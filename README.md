# 스마트창문 - 임베디드시스템(5조)
[시연 영상](https://drive.google.com/file/d/1Mtc5kd34DYA2gDyHuz0GIipPqfxOz5GU/view) <br>

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

## 👬 팀원 소개

<div>
  <table>
    <tr>
      <th>Profile</th>
      <th>Role</th>
    </tr>
    <tr>
      <td align="center">
        <a href="https://github.com/combikms">
          <img src="https://avatars.githubusercontent.com/u/156290648?v=4" width="100" height="80" alt=""/>
          <br/>
          <sub><b>강인석</b></sub>
        </a>
      </td>
      <td>
        - 주요 기능 개발 (예약 및 취소, 업체 등록, 대기열 관리, 찜, 내 정보 등) <br>
        - FireStore 데이터베이스 설계 <br>
        - Frontend UI 배치 <br>
        - WaitFree 기능에 OpenAPI 연동 <br>
      </td>
   </tr>
   <tr>
      <td align="center">
        <a href="https://github.com/GitgaJini">
          <img src="https://avatars.githubusercontent.com/u/112643202?v=4" width="100" height="80" alt=""/>
          <br/>
          <sub><b>김은진</b></sub>
        </a>
      </td>
      <td>
        - 모든 화면 설계 및 디자인 <br>
        - 네비바/둘러보기/FAQ 페이지 구현 <br>
        - 아이콘/애니메이션 제작 및 글귀 작성 <br>
        - 주도, 기능 제안 및 구체화
      </td>
   </tr>
   <tr>
      <td align="center">
        <a href="https://github.com/CF-SJG">
          <img src="https://avatars.githubusercontent.com/u/141010553?v=4" width="100" height="80" alt=""/>
          <br/>
          <sub><b>이민규</b></sub>
        </a>
      </td>
      <td>
        - 주요 기능 개발 (계정 관련 기능, FCM, 신고/문의 기능) <br>
        - Firebase프로젝트 관리 <br>
        - 사용자 데이터베이스 관리 및 통합 <br>
        - 버그 테스트 및 기능 측면 수정
      </td>
   </tr>
     <tr>
      <td align="center">
        <a href="https://github.com/dhdheb">
          <img src="https://avatars.githubusercontent.com/u/144876081?v=4" width="100" height="80" alt=""/>
          <br/>
          <sub><b>이영정</b></sub>
        </a>
      </td>
      <td>
        - 주요 기능 개발: 현재 위치 기반 지도 API 통합, 주소 변환 및 거리 계산 <br>
        - QR 코드 생성 및 딥 링크 처리: 예약 시스템과 라우팅 <br>
        - 검색 정렬 및 필터링: 혼잡도/거리순 정렬과 주변 매장 필터링 구현 <br>
        - UI 및 기능 테스트: UX 개선을 위한 UI 일부 수정과 기능 테스트
      </td>
   </tr>
  </table>
</div>
