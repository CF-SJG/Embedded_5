# 스마트창문 - 임베디드시스템(5조)
[시연 영상](https://drive.google.com/file/d/1Mtc5kd34DYA2gDyHuz0GIipPqfxOz5GU/view) <br>

---

## 👋 아이디어 선정 및 동기
현대 사회에서 창문을 열고 닫는 단순한 동작조차 환경적 요인이나 개인적 상황에 따라 불편함을 초래할 수 있다. 예를 들어, 실내에 머무는 시간이 길어 환기가 필요하거나 창문을 열기 어려운 경우, 갑작스러운 비가 내릴 때 외출 중이라 창문을 닫기 어려운 경우가 발생할 수 있다. 특히, 밤에는 잠을 방해하지 않도록 암막 환경이 필요하거나 아침에 자연스럽게 밝은 빛을 받아 일어날 수 있는 환경이 요구되기도 한다.
이와 같은 불편함을 해소하고, 보다 편리하고 안전한 생활 환경을 조성하기 위해 스마트 창문 시스템을 설계했다. 본 시스템은 자동화된 창문 및 블라인드 제어 기능을 제공하며, 환경 변화에 신속히 대응하고 사용자 편의성을 극대화하며, 이를 통해 생활의 질을 높이고, 에너지 효율을 향상시키는 것을 목표로 하였다.


<br>

---

## 🏆 주요기능 소개
- 실시간 대기 상태 제공: 사용자는 앱을 통해 현재의 대기 시간을 실시간으로 확인할 수 있습니다.
- 간편한 예약 및 취소: 앱을 통해 손쉽게 예약을 하고 필요한 경우 취소할 수 있습니다.
- 운영 효율성 향상: 서비스 제공자는 대기열 관리를 더욱 효과적으로 수행함으로써 고객 경험을 개선하고 운영 효율성을 높일 수 있습니다.
  
<br>

---

## ✨ 주요 기능

### 수동/자동 모드 설정
블루투스를 통해 사용자가 수동 모드와 자동 모드 간 전환이 가능하다.
수동 모드 : 사용자가 직접 창문 및 블라인드를 원격으로 열고 닫을 수 있다.
자동 모드 : 빗물 감지 센서를 통해 비가 올 때 창문이 자동으로 닫힌다. 센서가 3회 이상 연속으로 물을 감지할 경우 창문이 닫힌다.

<br><br><br>


### 초음파 센서를 이용한 장애물 감지
창문이 닫히는 도중 장애물을 감지하면 즉시 작동을 멈추고 창문을 다시 연다.
장애물 존재 여부를 사용자에게 알리며, 자동 모드에서는 장애물이 사라진 후 환경 정보를 다시 확인하여 창문 제어를 재개한다.


<br><br><br>


### 조도 센서를 이용한 블라인드 자동 제어
실내 조도 상황에 따라 블라인드를 자동으로 올리거나 내린다.
밝기가 어두운 밤에는 블라인드를 내려 암막 환경을 조성하여 숙면을 돕고, 아침에는 밝아진 실내 환경을 만들어 사용자가 자연스럽게 깨어날 수 있도록 지원한다.


<br><br><br>

### 문의 및 신고
- 이메일 문의 및 신고: 사용자는 이메일을 통해 문의사항이나 신고 내용을 관리자에게 직접 전달할 수 있습니다.
<img src="https://github.com/user-attachments/assets/cf23c1c8-f344-41e9-acdb-ecc6b2f95320" width="300">
<img src="https://github.com/user-attachments/assets/1f3d6d11-468a-43b0-b0a6-ec7e028a7b9a" width="300">
<img src="https://github.com/user-attachments/assets/0ade3a98-f16e-4764-b0f3-4baf5c4d0c2c" width="300">

<br><br><br>

### 편의 기능
- 찜: 사용자는 마음에 드는 매장을 찜하여, 찜 목록에서 별도로 확인할 수 있습니다.
- 지도: 매장 위치 정보를 제공하여 사용자가 매장을 쉽게 찾을 수 있도록 돕습니다.
- 검색: 매장명이나 주소를 검색하여 원하는 매장을 손쉽게 찾을 수 있습니다.
- QR코드: QR코드를 스캔하여 간편하게 예약 페이지에 접속할 수 있습니다.
<img src="https://github.com/user-attachments/assets/4b749321-1dd5-48c8-8156-93c5879ad05e" width="300">
<img src="https://github.com/user-attachments/assets/0912bbe5-4e13-41fa-8f80-ccd9d4f16265" width="300">
<br>
<img src="https://github.com/user-attachments/assets/6c2e42c8-c6f4-43dc-abfc-e9f3f1acb139" width="300">
<img src="https://github.com/user-attachments/assets/b2aacce9-86a0-4a7c-9f46-d6c14ec1b165" width="300">
<br><br>

---

## 🛠️ 개발 환경 및 아키텍처
<img width="424" alt="image" src="https://github.com/user-attachments/assets/3663895a-50e4-40eb-961a-e1f4ccb3ee21" />
<br>
<img width="446" alt="image" src="https://github.com/user-attachments/assets/2022e46f-c938-40bf-99f2-94ae9c919d01" />


### 서버 사이드
- Firebase Cloud Firestore: 데이터 저장 및 관리를 위해 사용되며, 실시간 데이터 동기화를 지원합니다.
- Firebase Cloud Messaging (FCM): 사용자에게 실시간 알림을 전송하기 위해 사용됩니다.
- Naver Cloud Platform with Flask: Notification Event Handler 서버로, FCM을 통한 알림 이벤트를 관리합니다.
  
### 클라이언트 사이드
- Flutter App에서 사용자 인터페이스를 제공하며, Firebase와 통신하여 데이터를 실시간으로 업데이트하고 받아옵니다.
  
### 인증
- Google OAuth: Google 계정을 통한 인증을 지원합니다.
- Kakao OAuth: 카카오 계정을 통한 인증을 지원합니다.
- Firebase Authentication: 사용자 인증을 관리합니다.

### 통합된 서비스
- Google Maps API: 매장의 위치를 지도에 표시합니다.
- QR Code Integration: QR 코드를 스캔하여 간편하게 예약 페이지로 연결합니다.
- Mailer: 고객 문의, 신고 내용을 관리자의 이메일로 전송합니다.
- Location: 디바이스의 현재 위치를 기반으로 주변 매장을 검색합니다.

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
