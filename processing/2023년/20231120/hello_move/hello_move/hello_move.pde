int x = -160; // x라는 변수를 만들어줍니다.

void setup() {
  size(300, 300);
  fill(125, 0, 250);
  textSize(50);
}

void draw() {
  background(255); 
  text("HELLO", x, 50); // (x,50)인 곳에 hello를 출력합니다.
  x++;                  // x를 1씩 더합니다.
}
