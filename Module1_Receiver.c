#include <stdio.h>
#include <pthread.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>

#define CW 0 
#define CCW 1 
#define COM_UART "/dev/ttyAMA0" // �۽����� ���
#define BT_UART "/dev/ttyAMA1" // ������� ���
#define BAUD_RATE 115200
#define SPEAKER_PIN 18

// ���� �Ӱ谪 ����
#define LIGHT_THRESHOLD 200

// ���� ������ ����ü
typedef struct {
    int motorCommand;     // â�� ���� ���� ��� (0: ����, 1: ����, 2: �ݱ�)
    int speakerCommand;   // ����Ŀ ���� ��� (0: ����, 1: �����˸�-ª��������, 2: �����˸�-�������)
    int isWet;           // ���� ���� ���� (0: �� �ȿ�, 1: �� ������)
    int lightLevel;      // ���� ���� �� (0-1023, ���� Ŭ���� ����)
    int controlMode;     // ���� ��� ���� (0: ����-������� ����, 1: �ڵ�-���� ��� ����)
    int windowState;     // ���� â�� ���� (0: ����, 1: ����)
    int blindCommand;    // ����ε� ���� ��� (0: ����, 1: �ø���, 2: ������)
    int blindState;      // ���� ����ε� ���� (0: �ö�, 1: ������)
    int choState;        // ��ֹ� ���� ���� (0: ��ֹ� ����, 1: ��ֹ� ����)
    pthread_mutex_t mutex;
} SharedData;

SharedData sharedData;
int bt_fd; // ������� UART
int com_fd; // ��ſ� UART

// GPIO �� �迭 (����)
int pin_arr[4] = { 12, 16, 20, 21 };
int blind_pins[4] = { 23, 24, 25, 26 };
int two_phase[4][4] = {
    {1, 1, 0, 0},
    {0, 1, 1, 0},
    {0, 0, 1, 1},
    {1, 0, 0, 1}
};

// �ʱ�ȭ �Լ�
void init_Step() {
    for (int i = 0; i < 4; i++) {
        pinMode(pin_arr[i], OUTPUT);
        digitalWrite(pin_arr[i], LOW);
    }
    for (int i = 0; i < 4; i++) {
        pinMode(blind_pins[i], OUTPUT);
        digitalWrite(blind_pins[i], LOW);
    }
    pinMode(SPEAKER_PIN, OUTPUT);
}

// ���� ���� �Լ�
void two_Phase_Rotate(int steps, int dir) {
    for (int i = 0; i < steps; i++) {
        for (int j = 0; j < 4; j++) {
            if (dir == CW) {
                digitalWrite(pin_arr[j], two_phase[(3 - i % 4)][j]);
            }
            else {
                digitalWrite(pin_arr[j], two_phase[i % 4][j]);
            }
        }
        delay(2);
    }
}

//����ε� ���� ���� �Լ�
void blind_Motor_Control(int steps, int dir) {
    for (int i = 0; i < steps; i++) {
        for (int j = 0; j < 4; j++) {
            if (dir == CW) {
                digitalWrite(blind_pins[j], two_phase[(3 - i % 4)][j]);
            }
            else {
                digitalWrite(blind_pins[j], two_phase[i % 4][j]);
            }
        }
        delay(2);
    }
}

// ����Ŀ ���� �Լ�
void playSound(int command) {
    if (command == 1) { // ���� �˸�
        digitalWrite(SPEAKER_PIN, HIGH);
        delay(100);
        digitalWrite(SPEAKER_PIN, LOW);
        delay(100);
        digitalWrite(SPEAKER_PIN, HIGH);
        delay(100);
        digitalWrite(SPEAKER_PIN, LOW);
    }
    else if (command == 2) { // ���� �˸�
        digitalWrite(SPEAKER_PIN, HIGH);
        delay(200);
        digitalWrite(SPEAKER_PIN, LOW);
    }
}

void checkSensorData() {
    pthread_mutex_lock(&sharedData.mutex);
    if (sharedData.controlMode == 1) { // �ڵ� ����� ����
        int shouldClose = 0;

        // ���� ���� ���� üũ
        if (sharedData.isWet == 1) {
            shouldClose = 1;
        }

        // â�� ���¿� ���� ����
        if (shouldClose && sharedData.windowState == 1) { // �������� ���� �ݱ�
            sharedData.motorCommand = 2; // �ݱ�
            sharedData.speakerCommand = 2;
            printf("[AUTO] Closing window due to rain\n");
        }
    }
    pthread_mutex_unlock(&sharedData.mutex);
}

void checkLightLevel() {
    pthread_mutex_lock(&sharedData.mutex);
    if (sharedData.controlMode == 1 && sharedData.windowState == 0) { // �ڵ� ��� & â�� ���� ����
        if (sharedData.lightLevel > LIGHT_THRESHOLD &&
            sharedData.blindCommand == 0 &&
            sharedData.blindState == 0) { // ���, ��� ����, ����ε� �ø� ����
            sharedData.blindCommand = 2; // ����ε� ������
            printf("[AUTO] Lowering blind due to high light level: %d\n", sharedData.lightLevel);
        }
        else if (sharedData.lightLevel <= LIGHT_THRESHOLD &&
            sharedData.blindCommand == 0 &&
            sharedData.blindState == 1) { // ��Ӱ�, ��� ����, ����ε� ���� ����
            sharedData.blindCommand = 1; // ����ε� �ø���
            printf("[AUTO] Raising blind due to low light level: %d\n", sharedData.lightLevel);
        }
    }
    pthread_mutex_unlock(&sharedData.mutex);
}

// ������� ���� ������
void* bluetoothThread(void* arg) {
    char buffer[100] = { 0 };
    int idx = 0;

    while (1) {
        if (serialDataAvail(bt_fd)) {
            char c = serialGetchar(bt_fd);

            if (c == '\n' || c == '\r') {
                buffer[idx] = '\0';

                char* cmd = buffer;
                while (*cmd == ' ') cmd++;
                char* end = cmd + strlen(cmd) - 1;
                while (end > cmd && (*end == ' ' || *end == '\n' || *end == '\r')) *end-- = '\0';

                printf("Debug - Cleaned command: '%s'\n", cmd);

                pthread_mutex_lock(&sharedData.mutex);
                if (strcmp(cmd, "A") == 0) {
                    sharedData.controlMode = 1;
                    printf("Switched to AUTO mode\n");
                }
                else if (strcmp(cmd, "M") == 0) {
                    sharedData.controlMode = 0;
                    printf("Switched to MANUAL mode\n");
                }
                else if (sharedData.controlMode == 0) {
                    if (strcmp(cmd, "O") == 0 && sharedData.windowState == 0) {
                        sharedData.motorCommand = 1;
                        sharedData.speakerCommand = 1;
                        printf("[MANUAL] Opening window\n");
                    }
                    else if (strcmp(cmd, "C") == 0 && sharedData.windowState == 1) {
                        sharedData.motorCommand = 2;
                        sharedData.speakerCommand = 2;
                        printf("[MANUAL] Closing window\n");
                    }
                    else {
                        printf("[MANUAL] Invalid command for current window state\n");
                    }
                }
                pthread_mutex_unlock(&sharedData.mutex);

                idx = 0;
                memset(buffer, 0, sizeof(buffer));
            }
            else if (idx < sizeof(buffer) - 1) {
                buffer[idx++] = c;
            }
        }
        delay(10);
    }
    return NULL;
}

void* comUartThread(void* arg) {
    char buffer[100] = { 0 };
    int idx = 0;

    while (1) {
        if (serialDataAvail(com_fd)) {
            char c = serialGetchar(com_fd);
            if (c == '\n') {
                buffer[idx] = '\0';
                printf("Raw received data: %s\n", buffer);

                int wet, light, cho;
                if (sscanf(buffer, "W:%d,L:%d,U:%d", &wet, &light, &cho) == 3) {
                    pthread_mutex_lock(&sharedData.mutex);
                    sharedData.isWet = wet;
                    sharedData.lightLevel = light;
                    sharedData.choState = cho;
                    printf("Parsed sensor values - Rain: %d, Light: %d, Obstacle: %d\n",
                        wet, light, cho);

                    if (cho == 1 && sharedData.motorCommand == 2) {
                        printf("*** Obstacle detected! Stopping closing operation ***\n");
                        sharedData.motorCommand = 0;
                    }

                    pthread_mutex_unlock(&sharedData.mutex);

                    if (sharedData.controlMode == 1) {
                        checkSensorData();
                        checkLightLevel();
                    }
                }

                idx = 0;
                memset(buffer, 0, sizeof(buffer));
            }
            else {
                if (idx < sizeof(buffer) - 1) {
                    buffer[idx++] = c;
                }
            }
        }
        delay(10);
    }
    return NULL;
}

void* motorThread(void* arg) {
    while (1) {
        pthread_mutex_lock(&sharedData.mutex);
        int command = sharedData.motorCommand;

        if (command == 1) {
            printf("Motor: Opening window\n");
            two_Phase_Rotate(11264, CCW);
            sharedData.windowState = 1;
            printf("Window is now open\n");
            sharedData.motorCommand = 0;
        }
        else if (command == 2) {
            printf("Motor: Starting to close window\n");
            int obstacle_detected = 0;

            for (int i = 0; i < 11264; i += 100) {
                if (sharedData.choState == 1) {
                    printf("!!! OBSTACLE DETECTED at step %d - STOPPING AND REVERSING !!!\n", i);

                    pthread_mutex_unlock(&sharedData.mutex);
                    printf("Reversing motor for %d steps\n", i);
                    two_Phase_Rotate(i, CCW);

                    pthread_mutex_lock(&sharedData.mutex);
                    sharedData.motorCommand = 0;
                    sharedData.windowState = 1;
                    obstacle_detected = 1;
                    printf("Motor reversed and stopped - Window is now open\n");
                    pthread_mutex_unlock(&sharedData.mutex);
                    break;
                }

                pthread_mutex_unlock(&sharedData.mutex);
                two_Phase_Rotate(100, CW);
                pthread_mutex_lock(&sharedData.mutex);
                printf("Closing progress: %d/11264\n", i);
            }

            if (obstacle_detected) {
                sharedData.windowState = 1;
                printf("Window remains open due to obstacle\n");
            }
            else {
                sharedData.windowState = 0;
                printf("Window is now closed completely\n");
            }
            sharedData.motorCommand = 0;
        }

        pthread_mutex_unlock(&sharedData.mutex);
        delay(10);
    }
    return NULL;
}

void* blindThread(void* arg) {
    while (1) {
        pthread_mutex_lock(&sharedData.mutex);
        int command = sharedData.blindCommand;
        if (command != 0 && sharedData.windowState == 0) {
            printf("Blind Motor: Executing command %d\n", command);
            if (command == 1 && sharedData.blindState == 1) {
                blind_Motor_Control(10240, CW);
                sharedData.blindState = 0;
                printf("Blind is now open\n");
            }
            else if (command == 2 && sharedData.blindState == 0) {
                blind_Motor_Control(10240, CCW);
                sharedData.blindState = 1;
                printf("Blind is now closed\n");
            }
            sharedData.blindCommand = 0;
        }
        else if (command != 0) {
            printf("Cannot operate blind: Window must be closed first\n");
            sharedData.blindCommand = 0;
        }
        pthread_mutex_unlock(&sharedData.mutex);
        delay(10);
    }
    return NULL;
}

void* speakerThread(void* arg) {
    while (1) {
        pthread_mutex_lock(&sharedData.mutex);
        int command = sharedData.speakerCommand;
        if (command != 0) {
            printf("Speaker: Playing sound %d\n", command);
            playSound(command);
            sharedData.speakerCommand = 0;
        }
        pthread_mutex_unlock(&sharedData.mutex);
        delay(10);
    }
    return NULL;
}

int main() {
    if (wiringPiSetupGpio() == -1) {
        printf("WiringPi initialization failed\n");
        return 1;
    }

    com_fd = serialOpen(COM_UART, BAUD_RATE);
    if (com_fd < 0) {
        printf("Unable to open Communication UART\n");
        return 1;
    }

    bt_fd = serialOpen(BT_UART, BAUD_RATE);
    if (bt_fd < 0) {
        printf("Unable to open Bluetooth UART\n");
        serialClose(com_fd);
        return 1;
    }

    init_Step();
    pthread_mutex_init(&sharedData.mutex, NULL);

    // �ʱⰪ ����
    sharedData.motorCommand = 0;
    sharedData.speakerCommand = 0;
    sharedData.controlMode = 0;
    sharedData.windowState = 0;
    sharedData.blindState = 0;
    sharedData.isWet = 0;
    sharedData.blindCommand = 0;
    sharedData.choState = 0;

    printf("System started in MANUAL mode\n");
    printf("Bluetooth Commands:\n");
    printf("A - Switch to AUTO mode\n");
    printf("M - Switch to MANUAL mode\n");
    printf("O - Open window (MANUAL mode only)\n");
    printf("C - Close window (MANUAL mode only)\n");


    pthread_t bluetooth_thread, com_uart_thread, motor_thread,
        speaker_thread, blind_thread;

    pthread_create(&bluetooth_thread, NULL, bluetoothThread, NULL);
    pthread_create(&com_uart_thread, NULL, comUartThread, NULL);
    pthread_create(&motor_thread, NULL, motorThread, NULL);
    pthread_create(&speaker_thread, NULL, speakerThread, NULL);
    pthread_create(&blind_thread, NULL, blindThread, NULL);

    pthread_join(bluetooth_thread, NULL);
    pthread_join(com_uart_thread, NULL);
    pthread_join(motor_thread, NULL);
    pthread_join(speaker_thread, NULL);
    pthread_join(blind_thread, NULL);

    pthread_mutex_destroy(&sharedData.mutex);
    serialClose(com_fd);
    serialClose(bt_fd);
    return 0;
}
