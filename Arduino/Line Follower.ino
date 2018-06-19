//sensor array
int s1= A0;
int s2= A1;
int s3= A2;
int s4= A3;
int s5= A4;

//sensor value to be used in sencheck
int sen1= 0;
int sen2= 0;
int sen3= 0;
int sen4= 0;
int sen5= 0;


int refval=250; //referance value to decide black and white

int lm1=4,lm2=5,lm3=6,lm4=7; //motor pin config


void setup() {
  Serial.begin(9600); //setting up the baud rate
  //setting the input sensors
  pinMode(s1,INPUT);
  pinMode(s2,INPUT);
  pinMode(s3,INPUT);
  pinMode(s4,INPUT);
  pinMode(s5,INPUT);
  //setting the output pins of motors
  pinMode(lm1,OUTPUT);
  pinMode(lm2,OUTPUT);
  pinMode(lm3,OUTPUT);
  pinMode(lm4,OUTPUT);
  // put your setup code here, to run once:

}

void loop() {


   sensor_check(); //calling sencheck function to check value of sensors
   
   //this code will work on 5 array ir sensors too....just uncomment the sencheck part of sensor 1 and 5
   
   if((sen3==1 && sen2==1 && sen4==1)||(sen3==1 && sen1==0 && sen2==0 && sen4==0 && sen5==0))  //if all detect white; move forward
   {
      pwm_forward(1,1); 
   }
   else if((sen4==1 && sen5==1) || sen5==1 || sen4==1 || (sen3==1 && sen4==1)) 
   { /*if only the right sensors are on the line then the bot must have moved a bit left so it must turn right*/
     right();
     //pwm_right(1,2);
    }
   else if((sen1==1 && sen2==1) || sen1==1 || sen2==1 || (sen2==1 && sen3==1))
   {/*if only the left sensors are on the line then the bot must have moved a bit right so it must turn left*/
      left();
      //pwm_left(1,2);
    }
  else if(sen1==0 && sen2==0 && sen3==0 && sen4==0 && sen5==0)
    {//if all sensors detect black then we must go back
      pwm_back(1,1);
    }

}
void sensor_check()
{
  /*if(analogRead(s1)>=refval)
    sen1=1;
  else
    sen1=0;
  */
  
  if(analogRead(s2)>=refval)
    sen2=1;
  else
    sen2=0;  
                           
  if(analogRead(s3)>=refval)
    sen3=1;
  else
    sen3=0;
    
  if(analogRead(s4)>=refval)
    sen4=1;
  else
    sen4=0;
    
  /*if(analogRead(s5)>=refval)
    sen5=1;
  else
    sen5=0;
  */
  }

void pwm_forward(int i,int j)
{//slow forward
  forward();
  delay(i);
  halt();
  delay(j);
}



void forward()
{
  digitalWrite(lm1,LOW);
 digitalWrite(lm2,HIGH);
 digitalWrite(lm4,LOW);
 digitalWrite(lm3,HIGH); 
}

void pwm_back(int i,int j)
{//slow backward
  backward();
  delay(i);
  halt();
  delay(j);
}

void backward()
{
  digitalWrite(lm2,LOW);
 digitalWrite(lm1,HIGH);
 digitalWrite(lm3,LOW);
 digitalWrite(lm4,HIGH);
 
  
}
void pwm_left(int i,int j)
{//slow left
  left();
  delay(i);
  halt();
  delay(j);
}

void left()
{
  digitalWrite(lm3,LOW);
  digitalWrite(lm4,HIGH);
  digitalWrite(lm1,LOW);
  digitalWrite(lm2,HIGH);
}

void pwm_right(int i,int j)
{//slow left
  right();
  delay(i);
  halt();
  delay(j);
}

void right()
{
  digitalWrite(lm4,LOW);
  digitalWrite(lm3,HIGH);
  digitalWrite(lm1,HIGH);
  digitalWrite(lm2,LOW);
}

void halt()
{
  digitalWrite(lm1,LOW);
  digitalWrite(lm2,LOW);
  digitalWrite(lm3,LOW);
  digitalWrite(lm4,LOW);
}