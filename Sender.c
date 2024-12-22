#include <wiringPi.h>
#include <wiringSerial.h>
#include <wiringPiI2C.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define WATER_SENSOR_PIN 4
#define LIGHT_SENSOR_ADDR 0x48
#define TRIG_PIN 23 // ������ TRIG ��
#define ECHO_PIN 24 // ������ ECHO ��
#define COM_UART "/dev/serial0"
#define BAUD_RATE 115200

// ���� ������ ����ü
typedef struct {
    int isWet;
    int lightLevel;
    int choState; // ������ ����
    pthread_mutex_t mutex;
} SensorData;

SensorData sensorData;
int com_fd; // UART ��� �ڵ�

// ������ ���� �Ÿ� ���� �Լ�
float getDistance() {
    // ������ ��ȣ �۽�
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    // ������ ��ȣ ���� ���
    while (digitalRead(ECHO_PIN) == LOW);

    // ��ȣ�� ���ƿ��� �ð� ���
    long startTime = micros();
    while (digitalRead(ECHO_PIN) == HIGH);
    long travelTime = micros() - startTime;

    // �Ÿ� ��� (����: 34300 cm/s)
    float distance = travelTime / 58.0;
    return distance;
}

// ������ ���� ������
void* ultrasonicThread(void* arg) {
    while (1) {
        float distance = getDistance();
        pthread_mutex_lock(&sensorData.mutex);
        if (distance > 16 && distance < 22) {
            sensorData.choState = 1;
            printf("Object detected! Distance: %.2f cm\n", distance);
        }
        else {
            sensorData.choState = 0;
            printf("No obstacle. Distance: %.2f cm\n", distance);
        }
        pthread_mutex_unlock(&sensorData.mutex);
        delay(500);
    }
    return NULL;
}

// ���� ���� ������
void* waterThread(void* arg) {
    int wetCount = 0;
    while (1) {
        if (digitalRead(WATER_SENSOR_PIN) == LOW) {
            wetCount++;
            if (wetCount >= 3) {
                pthread_mutex_lock(&sensorData.mutex);
                sensorData.isWet = 1;
                pthread_mutex_unlock(&sensorData.mutex);
                wetCount = 0;
            }
        }
        else {
            wetCount = 0;
            pthread_mutex_lock(&sensorData.mutex);
            sensorData.isWet = 0;
            pthread_mutex_unlock(&sensorData.mutex);
        }
        delay(1000);
    }
    return NULL;
}

// ���� ���� ������
void* lightThread(void* arg) {
    int i2c_fd = wiringPiI2CSetupInterface("/dev/i2c-1", LIGHT_SENSOR_ADDR);
    if (i2c_fd < 0) {
        printf("Light sensor initialization failed\n");
        return NULL;
    }

    while (1) {
        wiringPiI2CWrite(i2c_fd, 0x40 | LIGHT_SENSOR_ADDR);
        int lightVal = wiringPiI2CRead(i2c_fd);

        pthread_mutex_lock(&sensorData.mutex);
        sensorData.lightLevel = lightVal;
        pthread_mutex_unlock(&sensorData.mutex);

        delay(500);
    }
    return NULL;
}

// UART ���� ������ �۽� ������
void* uartThread(void* arg) {
    char buffer[100];
    while (1) {
        pthread_mutex_lock(&sensorData.mutex);
        snprintf(buffer, sizeof(buffer), "SEN:W:%d,L:%d,U:%d\n",
            sensorData.isWet, sensorData.lightLevel, sensorData.choState);
        pthread_mutex_unlock(&sensorData.mutex);

        // ����� �޽��� �߰�
        printf("Sending: %s", buffer);
        serialPuts(com_fd, buffer);
        delay(1000);
    }
    return NULL;
}

int main() {
    if (wiringPiSetupGpio() == -1) {
        printf("WiringPi setup failed\n");
        return 1;
    }

    // UART �ʱ�ȭ
    com_fd = serialOpen(COM_UART, BAUD_RATE);
    if (com_fd < 0) {
        printf("Unable to open Communication UART device\n");
        return 1;
    }

    // GPIO �ʱ�ȭ
    pinMode(WATER_SENSOR_PIN, INPUT);
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    digitalWrite(TRIG_PIN, LOW);
    delay(30);

    // ���� ������ �ʱ�ȭ
    pthread_mutex_init(&sensorData.mutex, NULL);
    sensorData.isWet = 0;
    sensorData.lightLevel = 0;
    sensorData.choState = 0;

    // ������ ����
    pthread_t water_thread, light_thread, uart_thread, ultrasonic_thread;
    pthread_create(&water_thread, NULL, waterThread, NULL);
    pthread_create(&light_thread, NULL, lightThread, NULL);
    pthread_create(&uart_thread, NULL, uartThread, NULL);
    pthread_create(&ultrasonic_thread, NULL, ultrasonicThread, NULL);

    printf("Sensor system started.\n");

    // ������ ���� ���
    pthread_join(water_thread, NULL);
    pthread_join(light_thread, NULL);
    pthread_join(uart_thread, NULL);
    pthread_join(ultrasonic_thread, NULL);

    // ����
    pthread_mutex_destroy(&sensorData.mutex);
    serialClose(com_fd);
    return 0;
}
