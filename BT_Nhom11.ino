#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <Firebase_ESP_Client.h>
#define WIFI_SSID "HAPPY FOOD"
#define WIFI_PASSWORD "29032810"
FirebaseData firebaseData;
LiquidCrystal_I2C lcd (0x27, 16,2);
int btn1 = 9;
int btn2 = 2;
int btn3 = 3;
int btn4 = 4;
int btn5 = 5;
int btn6 = 6;
int btn8 = 8;
int btn7 = 7;
int led01 = 1;
int led02 = 10;
int led03 = 11;
int led04 = 12;
int led05 = 13;
bool stt_led02 = true;
bool stt_led04 = true;
bool stt_all = true;
bool isPressed1 = false;
bool isPressed2 = false;
bool isPressed3 = false;
bool isPressed4 = false;
bool isPressed5 = false;
bool isPressed6 = false;
bool isPressed7 = false;
bool isPressed8 = false;
bool isPressed9=false;
unsigned long t_pre02 = 0;
unsigned long t_pre04 = 0;
unsigned long t_preAll = 0;
int mode_baochay =2;
int mode_phongkhach =3;
int mode_phongngu =3;
int mode_phongbep =2;
int mode_phongwc =2;
int current_t=0;
#define PASSWORD_LENGTH 4
const int password[PASSWORD_LENGTH] = {0,1,1};
// biến lưu trạng thái mật khẩu
int enteredPassword[PASSWORD_LENGTH];
int currentPasswordIndex = 0;
int lastButtonState = HIGH;
bool lightOn = false;
unsigned long lightStartTime;
unsigned long lightDuration = 5000; 
unsigned long t_pre=0;
void setup() {
  lcd.init();
  lcd.backlight();
  pinMode(btn1, INPUT);
  pinMode(btn2, INPUT);
  pinMode(btn3, INPUT);
  pinMode(btn4, INPUT);
  pinMode(btn5, INPUT);
  pinMode(btn6, INPUT);
  pinMode(btn7, INPUT);
  pinMode(btn8, INPUT);
  pinMode(led01, OUTPUT); 
  pinMode(led02, OUTPUT);     
  pinMode(led03, OUTPUT); 
  pinMode(led04, OUTPUT);
  pinMode(led05, OUTPUT); 
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print("Nhap Password:");
  Firebase.begin("doannhom11-362fa-default-rtdb.firebaseio.com", "AIzaSyCjpeZ5cng9rlZ-7sbwUiChhsFYfwHXxQs", "yDHcAMY9TVvULyM0PxjAsJGMBwd0h2lLubtTlZxj");
}
void loop() {
  // Ghi nhận trạng thái nút nhấn
  int button1State = digitalRead(btn1);
  int button2State = digitalRead(btn2);
 
  // Nếu nút nhấn 1 được nhấn
  if (button1State == HIGH && button2State == LOW) {
    isPressed1=true;
   }
   else{
    if(isPressed1){
      addDigitToPassword(0);//cộng 0 vào mật khẩu
    }
    isPressed1=false;
    }
  // Nếu nút nhấn 2 được nhấn
  if (button2State == HIGH && button1State == LOW) {
    isPressed2=true;
   }
   else{
    if(isPressed2){
      addDigitToPassword(1);//cộng 1 vào mật khẩu
    }
    isPressed2=false;
    }
  
  // Kiểm tra mật khẩu
  if (isPasswordCorrect()){
  lcd.clear();
  lcd.print(" Contactly !!!");
  clearEnteredPassword();
  delay(500);
  {
    if (!lightOn) {
      lightOn = true;
      lightStartTime = millis(); // Ghi nhận thời điểm bắt đầu đèn sáng
      digitalWrite(led01, 0);
      // Bật đèn
    }
  }
  }
   if(currentPasswordIndex == PASSWORD_LENGTH){
    lcd.print(" Fail !!!");
    delay(500);
  }
  // Tắt đèn nếu thời gian đã đủ
  if (lightOn && millis() - lightStartTime >= lightDuration) {
    lightOn = false;
    digitalWrite(led01, 1); // Tắt đèn
    clearEnteredPassword();
    lcd.clear();
    lcd.print("Nhap Password");
  }
   
  //Phòng khách
  if(digitalRead(btn8)==0){
    isPressed8=true;
  }
  else{
    if(isPressed8)
    {
    mode_phongkhach=(mode_phongkhach==3? mode_phongkhach = 1 : mode_phongkhach+1);
      if(mode_phongkhach == 2){
        t_pre02=millis();
        stt_led02 = 1;   
      }
    }
    isPressed8=false;
  }
    if(mode_baochay!=1){
  switch(mode_phongkhach){
    case 1:
        digitalWrite(led02,0);
      break;
    case 2:
        if(millis()-t_pre02>=500){
        digitalWrite(led02,stt_led02);
        stt_led02=!stt_led02;
        t_pre02=millis();
      }
      break;   
    default:
    digitalWrite(led02,1);
      break;
  }
    }
//Phòng ngủ
  if(digitalRead(btn6)==1){
    isPressed6=true;
  }
  else{
    if(isPressed6)
  {
    mode_phongngu=(mode_phongngu==3? mode_phongngu = 1 : mode_phongngu+1);
      if(mode_phongngu == 2){
        t_pre04=millis();
        stt_led04 = 1;   
      } 
      isPressed6=false;
  }
  }
    if(mode_baochay!=1){

  switch(mode_phongngu){
    case 1:
        digitalWrite(led04,0);
      break;
    case 2:
          if(millis()-t_pre04>=100){
        digitalWrite(led04,stt_led04);
        stt_led04=!stt_led04;
        t_pre04=millis();
      }
      break;
    case 3:
        digitalWrite(led04,1);
      break;   

  }
    }

//   //Phòng bếp
  if(digitalRead(btn5)==HIGH){
    isPressed5=true;
  }
  else{ 
     if(isPressed5){
      mode_phongbep=(mode_phongbep==2?mode_phongbep=1:mode_phongbep+1);
      isPressed5=false;
    }
  }
      if(mode_baochay!=1){
        switch(mode_phongbep){
          case 1:
            digitalWrite(led03,0);
          break;
          case 2:
              digitalWrite(led03,1);
          break;
      }
    }

//   //Phòng WC
    if(digitalRead(btn7)==HIGH){
    isPressed7=true;
  }
  else{ 
     if(isPressed7)
      mode_phongwc=(mode_phongwc==2?mode_phongwc=1:mode_phongwc+1);
      isPressed7=false;
  }
  if(mode_baochay!=1){
    switch(mode_phongwc){
      case 1:
        digitalWrite(led05,0);
      break;
      case 2:
          digitalWrite(led05,1);
      break; 
    }
}
 
//   //Nút tắt hết đèn khi ra khỏi nhà
  if(digitalRead(btn3)==0){
      isPressed3=true;
  }
  else{
        if(isPressed3){
          digitalWrite(led01,0);
          digitalWrite(led02,0);
          digitalWrite(led03,0);
          digitalWrite(led04,0);
          digitalWrite(led05,0);
          mode_phongkhach=3;
          mode_phongngu=3;
          mode_phongbep=2;
          mode_phongwc=2;
        }
        isPressed3=false;    
  }
  //Nút báo cháy

    if(digitalRead(btn4)==0){
    isPressed4=true;
  }
  else{ 
     if(isPressed4){
      mode_baochay=(mode_baochay==2?mode_baochay=1:mode_baochay+1);
      if(mode_baochay==1){
        t_preAll=millis();
        stt_all = 1;
      }
      if(mode_baochay==2){
      }
     }
      isPressed4=false;
    
  }
    switch(mode_baochay){
      case 1:
          if(millis()-t_preAll>=100){
              digitalWrite(led01,stt_all);
              digitalWrite(led02,stt_all);
              digitalWrite(led03,stt_all);
              digitalWrite(led04,stt_all);
              digitalWrite(led05,stt_all);
        stt_all=!stt_all;
        t_preAll=millis();
      }
      break;
  }
}
void addDigitToPassword(int digit) {
enteredPassword[currentPasswordIndex] = digit;
  currentPasswordIndex++;
  Serial.println("digit:");
        Serial.println(digit);
  // Reset chỉ số mật khẩu nếu đã nhập đủ
  if (currentPasswordIndex == PASSWORD_LENGTH-1&&isPasswordCorrect()==false) {
    currentPasswordIndex = 0;
     lcd.clear();
       lcd.print("Failed!");
       delay(500);
       lcd.clear();
       lcd.print("Nhap lai Password");
      clearEnteredPassword();
      digit=0;
  }
  // Cập nhật hiển thị mật khẩu trên LCD
  lcd.setCursor( 0, 1);
  lcd.print(digit);
  Serial.println(digit);
}
void clearEnteredPassword() {
  for (int i = 0; i < PASSWORD_LENGTH; i++) {
    enteredPassword[i] = 0;
  }
  currentPasswordIndex = 0;
  lcd.setCursor(0, 1);
}
bool isPasswordCorrect() {
  for (int i = 0; i < PASSWORD_LENGTH-1; i++) {
    if (enteredPassword[i] != password[i]) {
      return false;
    }
  }
  return true;
}

