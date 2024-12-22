# 스마트창문 - 임베디드시스템(5조)
--- 
## 👬 팀원 소개
### 이민규(20200797)
### 이영정(20200860)
### 박준수(20200493)
### 김은진(20220269)

<br>

---

## [시연 영상 링크](https://drive.google.com/file/d/1Mtc5kd34DYA2gDyHuz0GIipPqfxOz5GU/view) <br>
### 영상 흐름도
#### 창문 제어
1. 수동 모드 선택 후 창문 개방한다.
2. 자동 모드 변경 후 빗물 감지 센서를 이용한 창문 폐쇄한다.
3. 창문 폐쇄 중 장애물 인식 후 창문 개방한다.
4. 현재 상태 자동 모드이며, 빗물 감지 센서를 통해 다시 창문 개방한다.
   
<br>

#### 블라인드 제어
1. 조도값의 따라 어둡다면 암막 환경 조성을 위해 블라인드를 내린다.
2. 다시 밝아진다면 블라인드를 올린다.

<br>

---

## 👋 아이디어 선정 및 동기
현대 사회에서 창문을 열고 닫는 단순한 동작조차 환경적 요인이나 개인적 상황에 따라 불편함을 초래할 수 있다. 예를 들어, 실내에 머무는 시간이 길어 환기가 필요하거나 창문을 열기 어려운 경우, 갑작스러운 비가 내릴 때 외출 중이라 창문을 닫기 어려운 경우가 발생할 수 있다. 특히, 밤에는 잠을 방해하지 않도록 암막 환경이 필요하거나 아침에 자연스럽게 밝은 빛을 받아 일어날 수 있는 환경이 요구되기도 한다.
이와 같은 불편함을 해소하고, 보다 편리하고 안전한 생활 환경을 조성하기 위해 스마트 창문 시스템을 설계했다. 본 시스템은 자동화된 창문 및 블라인드 제어 기능을 제공하며, 환경 변화에 신속히 대응하고 사용자 편의성을 극대화하며, 이를 통해 생활의 질을 높이고, 에너지 효율을 향상시키는 것을 목표로 하였다.
  
<br>

---

## ✨ 주요 기능

### 수동/자동 모드 설정
블루투스를 통해 사용자가 수동 모드와 자동 모드 간 전환이 가능하다.
수동 모드 : 사용자가 직접 창문 및 블라인드를 원격으로 열고 닫을 수 있다.
자동 모드 : 빗물 감지 센서를 통해 비가 올 때 창문이 자동으로 닫힌다. 센서가 3회 이상 연속으로 물을 감지할 경우 창문이 닫힌다.

<br>

### 초음파 센서를 이용한 장애물 감지
창문이 닫히는 도중 장애물을 감지하면 즉시 작동을 멈추고 창문을 다시 연다.
장애물 존재 여부를 사용자에게 알리며, 자동 모드에서는 장애물이 사라진 후 환경 정보를 다시 확인하여 창문 제어를 재개한다.

<br>

### 조도 센서를 이용한 블라인드 자동 제어
실내 조도 상황에 따라 블라인드를 자동으로 올리거나 내린다.
밝기가 어두운 밤에는 블라인드를 내려 암막 환경을 조성하여 숙면을 돕고, 아침에는 밝아진 실내 환경을 만들어 사용자가 자연스럽게 깨어날 수 있도록 지원한다.

<br>

---

## 🛠️ 수정 사항
개발 과정에서 몇 가지 기술적 한계와 제한 조건에 직면하였고, 이를 해결하기 위해 여러 번의 테스트와 논의를 거쳤다. 하지만 일부 기능은 구현 과정에서 발생한 문제를 해결하지 못했다
다음은 해당 내용이다
<br>

### RTC 모듈을 이용한 스케줄 기능 제외
초기 설계에서는 RTC 모듈을 사용하여 특정 시간에 창문을 열고 닫는 스케줄 기능을 구현하려 했다. 그러나 테스트 과정에서 시간이 설정된 후 모드가 수동 또는 자동으로 변경될 때 작동이 정상적으로 이루어지지 않는 문제가 반복적으로 발생했다. 이로 인해 RTC 모듈이 다른 기능과 충돌을 일으키며 시스템 전체의 안정성을 저해할 가능성이 있다고 판단하여, 해당 기능을 제외하기로 결정했다.
스케줄 기능은 스마트 창문의 자동화를 더 편리하게 만드는 핵심적인 요소였으나, 안정성과 완성도를 고려하여 이를 과감히 제외한 것이 최선의 선택이라고 판단했다.
  
### 온·습도 센서 제외
온·습도 센서를 활용하여 창문의 상태를 제어하려 했었다. 예를 들어, 온도가 일정 수준 이상 높거나 습도가 일정 기준을 초과하는 경우 창문을 닫도록 설계하려 했다. 그러나 온·습도 센서를 라즈베리 파이와 연결해 데이터를 주기적으로 읽어오는 과정에서, 데이터가 잘 읽혀지는 경우와 읽히지 않는 경우가 교차로 발생하는 문제가 있었다. 또한, 라즈베리 파이 5에서는 간헐적으로 데이터 손실이 발생했고, 라즈베리 파이 4에서는 센서가 전혀 작동하지 않는 현상이 확인되었다. 이러한 기술적 문제를 해결하기 위해 많은 시도를 했으나, 제한된 시간 내에 안정적인 데이터를 확보하지 못했다. 이에 따라 온·습도 센서를 제외하기로 결정했다.
  
### LCD 디스플레이 제외
초기 구상에서는 LCD 디스플레이를 활용해 온·습도 정보를 출력하고 창문의 상태를 시각적으로 표시하려 했다. 그러나 온·습도 센서 기능이 제외됨에 따라 LCD 디스플레이의 활용성이 크게 줄어들었고, 프로젝트 전체에서 필수적인 요소로 보기는 어렵다는 판단이 들었다. 따라서 LCD 디스플레이 또한 최종 설계에서 제외하기로 했다.

### 기타 센서 및 부품 제외
프로젝트 초기에는 미세먼지 센서를 통해 공기 질에 따라 창문 상태를 제어하거나, 리미트 스위치를 추가하여 창문 위치를 더욱 정교하게 조작하려는 계획도 있었다. 그러나 미세먼지 센서와 리미트 스위치는 가격이 상대적으로 높고, 우리가 테스트할 수 있는 환경을 구축하기 어렵다는 현실적인 제약에 직면했으며, 이에 따라 비용 절감과 개발 효율성을 위해 이러한 부품들도 최종적으로 제외하기로 결정했다.

<br>

--- 

## 🏆 전체 시스템 구조
<img width="435" alt="그림1" src="https://github.com/user-attachments/assets/1151e07b-b13a-4bcc-9b34-713ee3eb345a" />

<br>

--- 

## 💻 제한 조건 구현 내용
스마트 창문 시스템을 개발하는 과정에서 다양한 제한 조건을 충족하기 위해 멀티스레드 환경과 프로세스 간 통신(IPC) 기법을 활용하여 시스템을 설계하고 구현했다. 이러한 설계는 복잡한 하드웨어와 소프트웨어 구성 요소 간의 효율적인 동작을 가능하게 하며, 동시에 안정성과 확장성을 유지하는 데 중요한 역할을 한다.
라즈베리 파이 모듈 1 : 라즈베리 파이 모듈 1은 시스템의 중심 제어 역할을 담당하며, 블루투스를 통해 사용자로부터 수동및 자동 모드 전환 명령을 수신하거나, 환경 데이터를 바탕으로 창문과 블라인드를 제어하는 기능을 수행한다. 이를 위해 멀티스레드를 활용하여 작업을 분리하고 독립적으로 실행될 수 있도록 구성하였다.
### Main Thread
시스템 초기화, UART 통신 설정, 스레드 생성 및 관리를 담당한다. 특히 블루투스를 통한 창문 제어 명령을 처리하며, 사용자 명령에 따라 모드를 변경하거나 환경 데이터를 바탕으로 제어 로직을 실행한다. UART 통신을 활용하여 모듈 2와 데이터를 주고받으며, IPC(프로세스 간 통신)를 통해 실시간으로 데이터를 처리하여 시스템을 조작할 수 있다.
### Worker Thread 1(블루투스 통신 + 수동/자동 모드 변경)
블루투스를 통해 사용자로부터 수동 또는 자동 모드 전환 명령을 수신하고, 이를 메인 스레드와 연동하여 시스템 상태를 업데이트 한다. 뮤텍스를 사용하여 모드 변경 작업 시 동시 접근 문제를 방지하고, 데이터 무결성을 보장한다.
### Worker Thread 2(스텝 모터 + 창문 제어)
창문을 여닫는 스텝 모터를 제어한다. UART로부터 전달된 환경 정보를 바탕으로 창문을 여닫거나, 수동 모드에서 블루투스 명령에 따라 창문 상태를 조작한다. 초음파 센서로 장애물이 감지되었을 경우 작업을 중단하고 경고를 메인 스레드로 전달한다.
### Worker Thread 3(스텝 모터 + 블라인드 제어)
조도 센서로부터 전달받은 밝기 데이터를 기반으로 블라인드를 제어한다. 낮에는 블라인드를 열어 자연광을 받아들이고, 밤에는 블라인드를 내려 암막 환경을 조성한다. 이 작업 역시 뮤텍스를 사용하여 다중 스레드 간의 데이터 충돌을 방지한다.
### 라즈베리 파이 모듈 2
라즈베리 파이 모듈 2는 환경 정보를 수집하고 이를 모듈 1로 전송하는 역할을 담당한다. 모듈 2는 다양한 센서를 관리하며, 데이터를 주기적으로 읽고 처리하는 작업을 멀티스레드 구조로 나누어 수행한다.
### Main Thread
시스템 초기화 및 UART 포트 설정을 담당한다. 환경 정보를 주기적으로 수집하여 데이터 패킷으로 포맷팅한 후, 이를 모듈 1로 전송한다. UART를 통한 통신은 안정성과 실시간성을 보장하며, 효율적인 데이터 처리를 가능하게 한다.
### Worker Thread 1(조도 센서 + 빗물 감지 센서 + 초음파 센서 데이터 수집)
각 센서로부터 데이터를 읽어와 메인 스레드로 전달한다. 조도 센서는 밝기를 측정하여 블라인드 제어에 사용되고, 빗물 감지 센서는 일정 기준 이상 3회 이상 연속적으로 물이 감지되었을 때 창문을 닫도록 신호를 보낸다. 초음파 센서는 창문이 닫힐 때 장애물을 감지하여 안전성을 확보한다.
### Worker Thread 2: UART 통신 데이터 처리 및 전송
Worker Thread 1에서 수집된 센서 데이터를 UART 프로토콜을 통해 모듈 1로 전송한다. 데이터를 효율적으로 포맷팅하고, 통신 중 오류를 방지하기 위한 에러 핸들링 로직도 포함되어 있다. 
### 멀티스레드 필수 활용
본 시스템은 다수의 센서 및 제어 장치를 동시에 관리해야 하므로, 멀티스레드를 활용하여 작업을 분리하고 병렬 처리를 통해 성능을 최적화하였다. 각 스레드가 독립적으로 동작하며, 작업 간 간섭을 최소화하여 시스템의 안정성을 보장하였다.
### IPC와 뮤텍스 활용
모듈 간 데이터 전송 과정에서 IPC 기법(UART 통신)을 활용하여 안정적이고 빠른 데이터 교환을 구현하였다. 또한, 다중 스레드 환경에서 발생할 수 있는 데이터 충돌을 방지하기 위해 뮤텍스를 활용하여 동기화를 구현하였다. 이를 통해 데이터 무결성과 시스템 안정성을 모두 확보할 수 있었다.

<br>

---

## 👋 코드 분석
### 라즈베리 파이 모듈1(블루투스 + 라즈베리 파이 모듈2 UART 통신)
#### - 모터 제어
창문을 열고 닫기 위해 모터를 제어한다.(스텝 모터 방식)
블라인드의 위치(올리기/내리기)도 모터로 조작한다.
#### - 센서 기반 제어 (자동 모드)
조도 센서: 주변 조명이 일정 임계값 이상 밝거나 어두운 경우 블라인드를 내리거나 올린다.
빗물 센서: 비가 감지되면 창문을 자동으로 닫는다.
장애물 감지 센서: 창문 닫힘 중 장애물을 감지하면 닫기를 멈추고 다시 여는 동작 수행한다.
#### - 수동 제어 (블루투스 명령)
사용자가 블루투스를 통해 창문을 열거나 닫고, 자동/수동 모드를 전환한다.
#### - 스피커 알림
창문 열림 및 닫힘에 따라 짧거나 긴 비프음을 출력한다.
#### <시나리오>
#### - 자동 모드 (AUTO)
비가 감지되면 창문을 자동으로 닫는다.
어두우면 블라인드를 내리고, 밝으면 블라인드를 올린다.
장애물이 감지되면 창문 닫기를 중단하고 다시 연다.
#### - 수동 모드 (MANUAL)
사용자가 블루투스 명령(O, C)으로 창문을 열거나 닫을 수 있다.
아래 5개의 특정한 작업을 담당하는 스레드를 통해 다중 스레드로 구성하여 병렬작업을 처리한다
센서 값을 업데이트 하는 동시에 업데이트 되는 센서 값을 읽어와 잘못된 값을 읽거나, 동작이 중단되는 스레드 간 데이터 충돌 및 동시 접근 문제를 방지하기 위해 뮤텍스를 사용한다.
<p>  
   BluetoothThread 블루투스 명령 수신<br>
   ComUartThread: 센서 데이터 수신<br>
   MotorThread: 창문 모터 제어<br>
   BlindThread: 블라인드 모터 제어<br>
   SpeakerThread: 스피커 알림 처리<br>
</p>

<br>

### 라즈베리 파이 모듈2(라즈베리 파이 모듈1 UART 통신)
#### - 라즈베리 파이 모듈 2
다양한 센서를 관리하며 환경 정보를 수집하고, 이를 모듈 1로 전송하는 역할을 수행한다. 이 시스템은 멀티스레드 구조를 기반으로 동작하며, 각 센서 데이터의 수집과 처리 작업을 독립적인 스레드에서 수행하여 효율성을 극대화한다. 또한, 뮤텍스를 사용하여 센서 데이터의 동시 접근 문제를 방지하고 데이터 무결성을 보장한다.
#### - 초음파 센서
초음파 신호를 송신(TRIG 핀)한 후 반사되어 돌아오는 시간을 측정(ECHO 핀) - 반환 시간(travel time)을 기반으로 거리를 계산: 거리(cm) = travel time(μs)/58
거리 범위가 16~22cm사이일 때 장애물이 존재한다고 판단하면, choState 를 업데이트한다.
#### - 빗물 감지 센서
GPIO 핀에서 센서 입력 값을 읽어 LOW상태일 경우 물이 감지됨을 의미한다.
연속 3회 이상 감지되면 isWet플래그를 활성화하여 모듈1로 전송한다.
#### - 조도 센서
I2C 프로토콜을 통해 센서로부터 조도 값을 읽어온다.
조도 값은 lightLevel변수에 저장되어 모듈1로 전달된다.
#### - UART 통신(데이터 전송)
모듈 2에서 수집된 모든 센서 데이터는 UART 프로토콜을 통해 모듈 1로 전송된다.
#### - 데이터 포맷 형태(SEN:W:<isWet>,L:<lightLevel>,U:<choState>)
데이터를 주기적으로 송신하며, 송신 전 포맷팅 및 에러 핸들링 로직이 포함된다.
#### - 공유 데이터 보호
센서 데이터(SensorData구조체)는 여러 스레드에서 동시에 읽고 쓰일 수 있기 때문에 뮤텍스를 활용하여 동기화한다.
isWet: 빗물 감지 상태
lightLevel: 밝기 값
choState: 장애물 감지 상태
#### - 데이터 접근 과정
잠금(pthread_mutex_lock) : 데이터를 읽거나 쓰기 전에 뮤텍스를 잠가 동시 접근을 방지한다.
작업 수행: 데이터를 읽거나 수정한다.
잠금 해제(pthread_mutex_unlock) : 작업 종료 후 뮤텍스를 해제하여 다른 스레드가 접근 가능하도록 한다.

<p>
   예시)<br>
   pthread_mutex_lock(&sensorData.mutex);<br>
   sensorData.isWet = 1;(빗물 감지 상태 업데이트)<br>
   pthread_mutex_unlock(&sensorData.mutex);<br>
</p>
  
<br>

---

## 👋 개발 시 문제점 및 해결 방법
본 시스템 개발 과정에서 다양한 기술적 문제점이 발생하였으며, 이를 해결하기 위해 하드웨어 및 소프트웨어적 관점에서 여러 방안을 설계 및 구현하였다. 다음은 주요 문제점과 그에 따른 해결 방안에 대한 상세 설명이다.
### 모듈 간 UART 연결 불안정
문제점 : 라즈베리 파이 모듈 1과 모듈 2 간 UART 통신 과정에서 데이터 전송 실패, 패킷 손실, 또는 간헐적인 연결 불안정 현상이 발생하였다. 이는 핀 배선 연결 오류나 서로 다른 baud rate설정이 주요 원인으로 확인되었다.
해결 방안 : UART 핀 배선과 포트를 재확인하여 전기적 연결 상태를 안정화하였다. 양쪽 모듈의 baud rate를 115200으로 통일하여 데이터 전송 속도와 호환성을 맞추었다. UART 통신 중 발생할 수 있는 오류를 감지하고 재전송하는 에러 핸들링 로직을 추가하여 데이터 무결성을 강화하였다.
### 블루투스와 UART 동시 사용 문제
문제점: 블루투스와 UART가 동시에 활성화될 경우, 라즈베리 파이의 통신 채널 간 간섭으로 인해 데이터 충돌 및 혼선이 발생하였다. 이는 블루투스와 UART 통신이 동일한 리소스를 경쟁적으로 사용하면서 나타난 문제로 파악되었다.
해결 방안: 블루투스를 정보 수집 모듈인 모듈 2와 연결하려고 시도하였으나, 연결 및 동작 과정에서 어려움이 발생하였다. 이를 해결하기 위해 블루투스를 정보 수신과 모터 제어를 담당하는 모듈1과 연결하도록 변경하였다. 소프트웨어적으로 블루투스와 UART가 서로 독립적으로 작동하도록 설계하여 각 통신 채널 간 간섭을 최소화하였다. 이를 위해 블루투스 스레드와 UART 스레드를 각각 분리하고, 각 스레드가 동기화되지 않도록 멀티스레드 구조를 최적화하였다.
### 센서 데이터 처리 지연 문제
문제점 : 조도 센서, 초음파 센서, 빗물 감지 센서 등 여러 센서로부터 데이터를 수집하고 처리하는 과정에서 처리 시간이 지연되면서 데이터 손실 또는 비효율적인 데이터 전송이 발생하였다.
해결 방안 : 센서 데이터 수집 주기를 최적화하여, 센서별 필요한 데이터만 효율적으로 수집하도록 조정하였다. 불필요한 빈도 높은 데이터 수집을 줄여 CPU 부하를 완화했다. 센서 데이터 전송 시 중요 데이터만 포함하도록 데이터 패킷 크기를 축소하였다.
### 창문 닫힘 중 장애물 감지 오작동
문제점 : 창문 닫힘 동작 중 초음파 센서가 장애물을 제대로 감지하지 못하거나, 감지 범위를 벗어난 장애물을 탐지하는 오작동이 발생하였다. 이는 초음파 센서의 배치와 작동 범위가 적절하지 않았기 때문으로 분석되었다.
해결 방안: 초음파 센서의 작동 범위를 측정하여, 장애물을 효과적으로 탐지할 수 있는 최적의 위치에 센서를 재배치하였다. 창문 닫힘 방향에 따라 센서의 각도와 높이를 조정하여 장애물 감지 정확도를 개선하였다. 장애물 탐지 시 창문 동작을 즉시 중단하고, 경고 신호를 사용자에게 전달하는 안전 로직을 추가하여 시스템의 안정성을 확보하였다.
  
<br>

---

## 👋 개선 방안
### 온·습도 센서를 활용한 다양한 환경 상황 대응
현재 시스템은 조도 센서와 초음파 센서를 중심으로 환경 데이터를 처리하고 있으나, 이를 보다 정교하게 확장하기 위해 온·습도 센서를 다시 활용하는 방안을 검토할 필요가 있다. 온·습도 센서는 실내 환경의 세부적인 변화와 상태를 감지할 수 있어, 더 다양한 환경 상황에 대응할 수 있는 시스템 설계가 가능하다. 특히, 온·습도 데이터를 통해 계절별, 시간대별로 환경을 세분화하고, 이에 따라 자동화된 블라인드 및 창문 제어가 이루어지도록 알고리즘을 개선할 수 있다. 이를 통해 시스템은 보다 실시간적이고 세밀한 제어를 제공하게 될 수 있다.
### 블라인드의 수동 조작 가능성 확보
현재 블라인드는 자동 제어를 중심으로 설계되어 있으나, 사용자의 편의성을 높이기 위해 수동 조작 기능을 추가하는 방안을 고려했다. 블루투스 명령 제어 부분에 기능을 추가하여 사용자가 블라인드의 상태를 원하는 대로 즉시 변경할 수 있도록 하는 것이 개선 부분이다. 이를 통해 사용자는 자동화 제어와 수동 조작 간의 전환이 가능해지며, 시스템의 유연성과 실용성이 더욱 높아질 것이다.
### 정보 수신 및 처리 과정의 우선순위 명확화
현재 시스템은 블루투스와 UART 간의 데이터 충돌 문제를 해결하면서 안정적인 통신 환경을 구현했으나, 향후 정보 수신 및 처리 단계에서의 우선순위를 더욱 명확히 할 필요가 있다. 예를 들어, 창문 제어와 블라인드 제어가 동시에 필요한 상황에서 우선적으로 처리해야 할 작업을 명확히 구분하고, 이를 소프트웨어적으로 최적화하여 데이터 병목 현상이나 처리 지연을 방지할 수 있다. 이를 통해 시스템의 응답성을 더욱 매끄럽게 개선할 수 있을 것이다.
### 초음파 센서 감지 안정성 강화
초음파 센서는 창문 및 블라인드 작동 중 장애물을 감지하는 중요한 역할을 한다. 하지만 감지 범위와 정확도가 환경적 요인에 따라 달라질 수 있어, 이를 보다 안정적으로 구현하기 위해 알고리즘의 보완이 필요하다. 초음파 센서의 감지 범위를 정확히 설정하고, 환경에 따라 가변적으로 조정될 수 있는 동적 알고리즘을 적용하여 감지 오류를 최소화할 수 있다고 판단된다. 
### 알고리즘 최적화를 통한 시스템의 효율성 강화
온·습도 및 조도 데이터를 조합하여 복합적인 환경 조건을 고려할 수 있도록 알고리즘을 개선하고, 초음파 센서의 장애물 감지와 관련된 코드 역시 세부적으로 최적화하여 안정적인 작동을 보장해야 한다. 이를 통해 전체 시스템의 데이터 처리 속도와 정확성을 높이고, 사용자가 신뢰할 수 있는 스마트 홈 환경을 제공할 수 있을 것이라고 기대된다.

  
<br>
