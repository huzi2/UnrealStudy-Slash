# UnrealStudy-Slash

<img width="798" alt="image" src="https://github.com/huzi2/UnrealStudy-Slash/assets/31639085/0f1197fe-405b-40c1-93ab-86e6ff45739d">
<img width="1405" alt="image" src="https://github.com/huzi2/UnrealStudy-Slash/assets/31639085/d7a6c61c-630e-4cd4-9cb7-11208634ae18">
<img width="1418" alt="image" src="https://github.com/huzi2/UnrealStudy-Slash/assets/31639085/5e559b88-0bb7-4955-b303-d44a9e46d458">
<img width="484" alt="image" src="https://github.com/huzi2/UnrealStudy-Slash/assets/31639085/ed442a92-743a-4da6-824b-9ddef6e106fa">
<img width="506" alt="image" src="https://github.com/huzi2/UnrealStudy-Slash/assets/31639085/4abfbbbd-7626-4a82-95a4-b08f79945deb">
<img width="410" alt="image" src="https://github.com/huzi2/UnrealStudy-Slash/assets/31639085/39f46374-f32f-4452-8214-8170841f5ad7">
<img width="678" alt="image" src="https://github.com/huzi2/UnrealStudy-Slash/assets/31639085/be774c97-826d-435a-8604-06773f651600">
<img width="1489" alt="image" src="https://github.com/huzi2/UnrealStudy-Slash/assets/31639085/b16214d7-ffcb-4cd2-bd30-c11eb68a2a3c">

## 프로젝트 영상

![Video Label](http://img.youtube.com/vi/haN_bnpZDMk/0.jpg)

기술 소개()

## 프로젝트 개요
언리얼 5.1 C++을 활용한 3인칭 액션 게임

## 사용 기술
- 향상된 입력(Enhanced Input)
- 캐릭터의 행동 구현(이동, 점프, 공격, 무기 집어넣거나 빼기, 구르기)
- 오픈 월드의 구현(해, 하늘)
- 랜드스케이를 활용한 산의 구현. 다양한 머티리얼을 사용
- 폴리지를 활용한 수풀, 나무 등의 구현
- 퀵셀 브리지를 통한 고품질의 에셋 사용
- 나나이트를 활용한 다수의 스태틱 메시 최적화
- 컨트롤 릭을 이용한 지형에 따른 발의 높낮이 수정
- IK릭과 IK리타가터를 이용한 서로 다른 스켈레톤의 애니메이션 리타깃팅
- 피격 방향에 따른 다양한 히트 애니메이션 구현
- 애니메이션 몽타주로 다양한 애니메이션 랜덤 재생 구현
- 메타사운드의 활용(사운드를 배열로 받아 랜덤 재생, 사운드의 피치와 볼륨을 조절해 다양한 사운드 재생)
- 나이아가라 이펙트를 활용한 아이템 이펙트 구현
- 아이템의 픽 업 기능과 액터의 히트 행동을 인터페이스로 만들어 해당 기능을 모듈식으로 구현
- 무기 트레일 이펙트 구현
- 프랙처를 통해 부숴지는 프랍 구현, 필드시스템으로 직접 프랙처 부수기
- BlueprintNativeEvent 활용해서 코드와 블루프린트를 같이 사용할 수 있는 함수 구현
- PawnSensingComponent을 활용한 AI 시각 처리
- 모션워핑으로 적이 루트 모션으로 공격 시 회전과 이동을 타겟 쪽으로 움직이면서 공격하도록 구현
- 애니메이션 블루프린트 템플릿으로 동일한 애니메이션 구성을 가진 액터를 쉽게 생성하도록 함

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

<img width="1093" alt="image" src="https://github.com/huzi2/UnrealStudy-Slash/assets/31639085/e4c9e559-17ff-4dbc-9584-616740155d6a">
<img width="1138" alt="image" src="https://github.com/huzi2/UnrealStudy-Slash/assets/31639085/60053711-b631-4dfe-a864-282fa1eb3b00">
<img width="1028" alt="image" src="https://github.com/huzi2/UnrealStudy-Slash/assets/31639085/5b419336-2f8d-4a0f-9262-cc0a1785356f">
<img width="578" alt="image" src="https://github.com/huzi2/UnrealStudy-Slash/assets/31639085/08c368d9-a7c6-49bc-9903-7fd14af8a989">
<img width="1257" alt="image" src="https://github.com/huzi2/UnrealStudy-Slash/assets/31639085/80ff97e9-0324-48cd-8b07-ea9d6e56046d">
<img width="556" alt="image" src="https://github.com/huzi2/UnrealStudy-Slash/assets/31639085/60f417e0-1474-4a34-a96a-497f9936584c">

캐릭터의 발 높이를 땅에 맞추는 컨트롤 릭

<img width="1900" alt="image" src="https://github.com/huzi2/UnrealStudy-Slash/assets/31639085/96a42293-eac0-494e-93a5-50c6a3f9a86e">
<img width="1910" alt="image" src="https://github.com/huzi2/UnrealStudy-Slash/assets/31639085/e320ef6a-dac2-4bf3-aeb3-0d2e5a631e00">

IK 릭과 IK 리타가터의 활용

<img width="1125" alt="image" src="https://github.com/huzi2/UnrealStudy-Slash/assets/31639085/a184b1ff-befc-45b5-899a-4cb3631efe23">

무기로 필드 시스템 생성해서 프랙처 부수기

<img width="799" alt="image" src="https://github.com/huzi2/UnrealStudy-Slash/assets/31639085/49c86208-a2da-47b0-9d53-340cb762aaa3">

프랙처 활용

<img width="1181" alt="image" src="https://github.com/huzi2/UnrealStudy-Slash/assets/31639085/b859f8ee-bbc4-4328-b480-3ac19ccfb468">

메타 사운드 활용

### 참고 자료 : Udemy - Unreal Engine 5 C++ The Ultimate Game Developer Course(https://www.udemy.com/course/unreal-engine-5-the-ultimate-game-developer-course/)

### 학습 기간 : 23.07.22 ~ 23.08.26 (5주)
