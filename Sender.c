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
#define TRIG_PIN 23 // 초음파 TRIG 핀
#define ECHO_PIN 24 // 초음파 ECHO 핀
#define COM_UART "/dev/serial0"
#define BAUD_RATE 115200

// 센서 데이터 구조체
typedef struct {
    int isWet;
    int lightLevel;
    int choState; // 초음파 상태
    pthread_mutex_t mutex;
} SensorData;

SensorData sensorData;
int com_fd; // UART 통신 핸들

// 초음파 센서 거리 측정 함수
float getDistance() {
    // 초음파 신호 송신
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    // 초음파 신호 수신 대기
    while (digitalRead(ECHO_PIN) == LOW);

    // 신호가 돌아오는 시간 계산
    long startTime = micros();
    while (digitalRead(ECHO_PIN) == HIGH);
    long travelTime = micros() - startTime;

    // 거리 계산 (음속: 34300 cm/s)
    float distance = travelTime / 58.0;
    return distance;
}

// 초음파 센서 스레드
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

// 수분 센서 스레드
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

// 조도 센서 스레드
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

// UART 센서 데이터 송신 스레드
void* uartThread(void* arg) {
    char buffer[100];
    while (1) {
        pthread_mutex_lock(&sensorData.mutex);
        snprintf(buffer, sizeof(buffer), "SEN:W:%d,L:%d,U:%d\n",
            sensorData.isWet, sensorData.lightLevel, sensorData.choState);
        pthread_mutex_unlock(&sensorData.mutex);

        // 디버깅 메시지 추가
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

    // UART 초기화
    com_fd = serialOpen(COM_UART, BAUD_RATE);
    if (com_fd < 0) {
        printf("Unable to open Communication UART device\n");
        return 1;
    }

    // GPIO 초기화
    pinMode(WATER_SENSOR_PIN, INPUT);
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    digitalWrite(TRIG_PIN, LOW);
    delay(30);

    // 공유 데이터 초기화
    pthread_mutex_init(&sensorData.mutex, NULL);
    sensorData.isWet = 0;
    sensorData.lightLevel = 0;
    sensorData.choState = 0;

    // 스레드 생성
    pthread_t water_thread, light_thread, uart_thread, ultrasonic_thread;
    pthread_create(&water_thread, NULL, waterThread, NULL);
    pthread_create(&light_thread, NULL, lightThread, NULL);
    pthread_create(&uart_thread, NULL, uartThread, NULL);
    pthread_create(&ultrasonic_thread, NULL, ultrasonicThread, NULL);

    printf("Sensor system started.\n");

    // 스레드 종료 대기
    pthread_join(water_thread, NULL);
    pthread_join(light_thread, NULL);
    pthread_join(uart_thread, NULL);
    pthread_join(ultrasonic_thread, NULL);

    // 정리
    pthread_mutex_destroy(&sensorData.mutex);
    serialClose(com_fd);
    return 0;
}
