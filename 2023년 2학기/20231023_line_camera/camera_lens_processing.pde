import processing.serial.*;  // processing.serial 라이브러리를 임포트합니다.

int i;  // 정수형 변수 i를 선언합니다.
Serial myPort;  // Serial 통신을 위한 객체 myPort를 선언합니다.
float data;  // 부동 소수점 변수 data를 선언합니다.
float[] line_data = new float[128];  // 길이 128의 부동 소수점 배열 line_data를 선언합니다.
int center_x = 0;  // 정수형 변수 center_x를 선언하고 초기값을 0으로 설정합니다.

public static int ON = 1;  // 정적 상수 ON을 1로 정의합니다.
public static int OFF = 0;  // 정적 상수 OFF를 0으로 정의합니다.

void setup() {
  String portName ;  // 문자열 변수 portName을 선언합니다.
  size (1000, 1000);  // 그래픽 화면 크기를 설정합니다.
  delay(1000);  // 1000밀리초(1초) 동안 대기합니다.

  println(Serial.list());  // 사용 가능한 시리얼 포트 목록을 출력합니다.
  portName = Serial.list()[2];  // 사용할 시리얼 포트의 이름을 선택합니다.

  myPort = new Serial(this, portName, 115200);  // 아두이노와의 시리얼 통신을 설정합니다.
}

void draw() {
  background(255);  // 화면 배경을 흰색(255)으로 설정합니다.

  // 데이터 포인트를 그래픽으로 그리기
  for (i = 0; i < 128; i++) {  // 0부터 127까지 반복합니다.
    fill(0, 0, 255);  // 파란색으로 설정합니다.
    rect(20 + 5 * i, 950, 5, -line_data[i]);  // 파란색 사각형을 그립니다.
  }

  // 중앙에 빨간 원 그리기
  fill(255, 0, 0);  // 빨간색으로 설정합니다.
  rect(20 + 5 * center_x, 950, 5, -400);  // 빨간색 사각형을 그립니다.
}

void serialEvent(Serial port) {
  int i, data_temp;  // 정수형 변수 i와 data_temp를 선언합니다.
  String input = port.readStringUntil('\n');  // 시리얼 데이터를 읽어서 input 문자열에 저장합니다.
  if (input != null) {  // input이 null이 아닌 경우
    input = trim(input);  // 문자열의 앞뒤 공백을 제거합니다.
    String[] values = split(input, " ");  // 문자열을 공백을 기준으로 분할합니다.

    // 데이터 길이 확인
    println(values.length);  // values 배열의 길이를 출력합니다.
    if (values.length == 129) {  // values 배열의 길이가 129인 경우
      for (i = 0; i < 128; i++) {  // 0부터 127까지 반복합니다.
        data_temp = int(values[i]);  // 문자열 값을 정수로 변환하여 data_temp에 저장합니다.

        // 데이터를 그래픽 좌표에 매핑
        line_data[i] = map(data_temp, 0, 256, 0, 800);  // 데이터를 그래픽 좌표에 매핑하여 line_data 배열에 저장합니다.
        print(line_data[i]);  // line_data의 값을 출력합니다.
        print(" ");  // 공백을 출력합니다.
      }

      // 중앙 위치 설정
      center_x = int(values[i]);  // values 배열의 마지막 값을 center_x로 설정합니다.
      print(center_x);  // center_x의 값을 출력합니다.
      println(" ");  // 줄 바꿈을 출력합니다.
    }
  }
}
