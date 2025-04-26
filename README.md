<h2 align='center'>GLIM SW Assignment by Taehwan-Heo</h2>

<p align='center'>
GLIM SW 직군 과제물 - 허태환
<br><br>
</p>

## Table of Contents

1. [Introduction](#1-introduction)
2. [Preview](#2-preview)
3. [Configuration](#3-configuration)
4. [Quick Start](#4-quick-start)
5. [Contact](#5-contact)

---

## 1. Introduction

본 저장소는 GLIM SW 직군 과제 수행을 위해 제작되었습니다.

### 1-1) 관련 이슈 목록

- [MFC 과제 관련 완료된 이슈 목록](https://github.com/or-m-or/GLIM-Assignment-by-Taehwan/issues?q=is%3Aissue%20state%3Aclosed)
- [모든 Commit Log](https://github.com/or-m-or/GLIM-Assignment-by-Taehwan/commits/master/)

### 1-2) 체크리스트

- [x] 세 번째 클릭 이후 클릭 지점 3개를 모두 지나가는 정원 1개 그리기
- [x] 클릭 지점 원 반지름을 사용자로부터 입력받기
- [x] 각 클릭 지점 원의 중심 좌표를 UI에 표시하기
- [x] 네 번째 클릭부터는 클릭 지점 원을 그리지 않기
- [x] 세 클릭 지점을 지나가는 정원의 내부는 채우지 않고, 외곽선 두께를 사용자로부터 입력받기
- [x] 클릭 지점 중 하나를 드래그할 때 정원이 실시간으로 이동하며 그려지도록 구현하기
- [x] [초기화] 버튼으로 모든 상태 초기화 및 다시 입력받기
- [x] [랜덤 이동] 버튼 클릭 시 클릭 지점 원을 랜덤하게 이동시키고 정원도 재생성하기
- [x] 랜덤 이동 및 정원 재생성을 초당 2회, 총 10번 자동 반복하며 메인 UI 프리징 없이 별도 스레드로 구현
- [x] MFC Dialog 기반 프로젝트로 작성하기
- [x] 클릭 지점 원과 정원 그릴 때 CDC 클래스를 사용하지 않고 비트맵 기반으로 처리하기

---

## 2. Preview

---

## 3. Configuration

- **MFC_Assignment** : MFC 기반 과제물
- **Programmers_Assignment** : 프로그래머스 알고리즘 문제 풀이 과제

```
GLIM-Assignment-by-Taehwan
├── 📁 MFC_Assignment         # 1. 유튜브 과제물 (MFC 애플리케이션)
└── 📁 Programmers_Assignment # 2. 프로그래머스 과제물
    ├── 2-1_codingtext.txt
    ├── 2-1_screenshot.png
    ├── 2-2_codingtext.txt
    ├── 2-2_screenshot.png
    ...
```

### 3-1) MFC 과제물 주요 클래스 설명

| 클래스명            | 설명                                                                                               |
| :------------------ | :------------------------------------------------------------------------------------------------- |
| `CMFCAssignmentDlg` | 메인 대화상자로, 사용자 입력(클릭, 드래그, 버튼 클릭 등)과 프로그램 흐름을 전체적으로 제어합니다.  |
| `Canvas`            | 백버퍼를 관리하며, 클릭 지점 원과 정원을 그리는 기능을 제공합니다. (CDC 없이 CImage 기반으로 구현) |
| `DotManager`        | 사용자가 클릭한 점(클릭 지점 원)들을 관리하고, 점 이동 및 정원 다시 그리는 기능을 제공합니다.      |
| `LabelHelper`       | 클릭 지점 좌표를 Static Text 컨트롤에 표시하거나, Canvas 위에 텍스트를 그릴 때 사용됩니다.         |
| `Utils`             | 세 점을 지나는 정원의 중심과 반지름을 계산하는 유틸리티 기능을 제공합니다.                         |

---

## 4. Quick Start

### 4-1) MFC 과제 실행 방법

> Visual Studio 2022 기준으로 개발되었습니다.
> ※ MFC 라이브러리 설치 필요 (Visual Studio 설치 시 MFC 패키지 포함 선택)

1. Visual Studio에서 `MFC_Assignment.sln` 솔루션 열기
2. Debug 또는 Release 모드 선택
3. `F5` 또는 `Ctrl + F5`로 실행

### 4-2) Programmers 과제 확인 방법

1. `/Programmers_Assignment` 폴더 열기
2. 각 과제 폴더 안의 `.txt` 파일 (코드) 및 `.png` 파일 (스크린샷) 확인

---

## 5. Contact

📧 hth815@naver.com <br>
☎ 010-4844-7192 <br>
