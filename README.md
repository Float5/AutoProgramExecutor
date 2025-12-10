# Auto Program Executor
작업에 필요한 프로그램과 웹사이트를 명령어 하나로 모두 실행시키는 프로그램

<br>
<br>

## 명령어
| 명령어 | 설명 | 예시 |
| :--- | :--- | :--- |
| `help` | 명령어 목록을 나타냅니다. | `help` |
| `exit` | 프로그램을 종료합니다. | `exit` |
| `clear` | 창의 모든 글자를 지웁니다. | `clear` |
| `ls` | 실행기(Executor)의 목록을 나타냅니다. | `ls` |
| `mkexe (이름)` | 새로운 실행기를 생성합니다. | `mkexe Work_Setup` |
| `rmexe (이름)` | 실행기를 삭제합니다. | `rmexe Work_Setup` |
| `modexe (이름) (-a or -r) (내용)` | 실행기의 내용을 추가/제거합니다. <br> 내용은 **W-(웹사이트)** 또는 **P-(파일 경로)** 형식입니다. <br> **공백은 `#`으로 대체해야 합니다.** | `modexe Work_Setup -a W-https://mail.google.com` |
| `exels (이름)` | 실행기의 내용 목록을 나타냅니다. | `exels Work_Setup` |
| **`run (이름)`** | **실행기 목록에 있는 모든 프로그램과 웹사이트를 실행합니다.** | `run Work_Setup` |
