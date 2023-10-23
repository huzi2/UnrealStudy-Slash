# UnrealStudy-Slash

<img width="1418" alt="image" src="https://github.com/huzi2/UnrealStudy-Slash/assets/31639085/5e559b88-0bb7-4955-b303-d44a9e46d458">
<img width="1489" alt="image" src="https://github.com/huzi2/UnrealStudy-Slash/assets/31639085/b16214d7-ffcb-4cd2-bd30-c11eb68a2a3c">

## 프로젝트 영상

![Video Label](http://img.youtube.com/vi/y67-mekP58E/0.jpg)

- [프로젝트 영상](https://youtu.be/y67-mekP58E)

## 프로젝트 개요

- 언리얼 5.1 C++을 활용한 3인칭 액션 게임

## 제작 기간

- 23.07.22 ~ 23.08.26 (5주)

## 개발 환경

- Unreal Engine 5.1(개발 시작) -> 5.3
- C++
- IDE : Visual Studio 2022

## 사용 기술([위키](https://github.com/huzi2/UnrealStudy-Slash/wiki))

### 게임 로직
- [오픈 월드](https://github.com/huzi2/UnrealStudy-Slash/wiki/게임-로직#오픈-월드)
- 무기
- 공격 충돌 박스
- 충돌 / 피격
- 향상된 입력

### 프로그래밍
- [인터페이스](https://github.com/huzi2/UnrealStudy-Slash/wiki/프로그래밍#인터페이스)
- [BlueprintImplementableEvent](https://github.com/huzi2/UnrealStudy-Slash/wiki/프로그래밍#blueprintimplementableevent)
- [BlueprintNativeEvent](https://github.com/huzi2/UnrealStudy-Slash/wiki/프로그래밍#blueprintnativeevent)
- 태그

### 애니메이션
- [지형에 따른 발의 높낮이 보정](https://github.com/huzi2/UnrealStudy-Slash/wiki/애니메이션#지형에-따른-발의-높낮이-보정)
- [애니메이션 리타기팅](https://github.com/huzi2/UnrealStudy-Slash/wiki/애니메이션#애니메이션-리타기팅)
- 애니메이션 블루프린트 템플릿
- 애니메이션 노티파이
- 피격 방향에 맞는 모션 출력
- 트레일 이펙트
- 모션 워핑
- 블렌드 스페이스

### UI
- 플레이어 HUD
- 게임 내 체력바

### 에셋과 데이터
- [메타사운드](https://github.com/huzi2/UnrealStudy-Slash/wiki/에셋과-데이터#메타사운드)
- [나나이트](https://github.com/huzi2/UnrealStudy-Slash/wiki/에셋과-데이터#나나이트)
- [프랙처](https://github.com/huzi2/UnrealStudy-Slash/wiki/에셋과-데이터#프랙처)
- [프랙처 부수기](https://github.com/huzi2/UnrealStudy-Slash/wiki/에셋과-데이터#프랙처-부수기)
- [퀵셀 브리지](https://github.com/huzi2/UnrealStudy-Slash/wiki/에셋과-데이터#퀵셀-브리지)

## 기술 스크린 샷

<img width="1144" alt="image" src="https://github.com/huzi2/UnrealStudy-Slash/assets/31639085/44255e9f-3784-4088-b27d-9da066e5bad0">

공격 애님 노티파이 활용(사운드 재생, 트레일 이펙트, 공격 종료 체크, 공격 콜리전 온/오프, 모션 워핑)

<img width="1148" alt="image" src="https://github.com/huzi2/UnrealStudy-Slash/assets/31639085/497267db-be6c-4a29-b6d1-3a40a5295dc1">

피격 애님 노티파이 활용(사운드 재생, 피격 위치에 따른 애니메이션 재생 위해 섹션 분리)

<img width="441" alt="image" src="https://github.com/huzi2/UnrealStudy-Slash/assets/31639085/148002af-8987-462f-af6a-d00bb57c466f">
<img width="452" alt="image" src="https://github.com/huzi2/UnrealStudy-Slash/assets/31639085/9acdbd1f-3a7e-4dde-b9a6-c75aeed9bf21">
<img width="579" alt="image" src="https://github.com/huzi2/UnrealStudy-Slash/assets/31639085/ecfb657c-7085-4253-ae24-dae7ee6c5ac7">
<img width="750" alt="image" src="https://github.com/huzi2/UnrealStudy-Slash/assets/31639085/d7e79b93-3591-465d-8c06-9f4db9ea87d0">

MainStates 애니메이션 블루프린트. 플레이어의 스테이트에 따른 애니메이션 블렌딩

<img width="951" alt="image" src="https://github.com/huzi2/UnrealStudy-Slash/assets/31639085/7ff51d49-3118-49fa-af5b-76937208cc0c">

컨트롤 릭을 통해 발 위치를 블렌딩하는 애니메이션 블루프린트

<img width="807" alt="image" src="https://github.com/huzi2/UnrealStudy-Slash/assets/31639085/b355f60c-a2a9-4292-b239-b00708e162e3">

MainStates, IK 두 애니메이션 블루프린트를 합치는 애니메이션 블루프린트

<img width="764" alt="image" src="https://github.com/huzi2/UnrealStudy-Slash/assets/31639085/d8ee4fce-dc54-48f2-81a2-080ec884899d">
<img width="253" alt="image" src="https://github.com/huzi2/UnrealStudy-Slash/assets/31639085/7dc6e225-cce7-46c9-b3c5-7151f127e1b4">
<img width="476" alt="image" src="https://github.com/huzi2/UnrealStudy-Slash/assets/31639085/c6b0720e-9908-4e26-907e-4663f2ea3df8">
<img width="754" alt="image" src="https://github.com/huzi2/UnrealStudy-Slash/assets/31639085/319f3153-274c-455e-b5ea-ed852d5f7a2f">

적 캐릭터 애니메이션 블루프린트 템플릿

<img width="1897" alt="image" src="https://github.com/huzi2/UnrealStudy-Slash/assets/31639085/c15daa6e-1af4-455a-aa86-9f690fbf2b16">

애니메이션 블루프린트 템플릿으로 생성한 애니메이션 블루프린트

### 참고 자료

- [Udemy - Unreal Engine 5 C++ The Ultimate Game Developer Course](https://www.udemy.com/course/unreal-engine-5-the-ultimate-game-developer-course/)
