int a=A8;
float b;
int count=1;
float R1=10000; //value of R1 on KY-013 NTC temperature sensor
float logR2,R2,T;
float c=0.001129148, d=0.000234125 , e=0.0000000876741; //these are steinhart-Hart coeficients for thermistor 
void setup() 
{
 Serial.begin(9600); 
}
//
void loop()
{
b=analogRead(a);
R2=R1*(1023.0/b-1.0); // calculation of resistance on the thermistor      FORMULA USED===(R1=R2(Vin/Vout-1))
logR2=log(R2);
T =(1.0/(c + d*logR2 + e*logR2*logR2*logR2)); //steinhart-Hart equation where c,d,e are constants and they change acourding to the thermistor ,,this will be in kelvin so convert
T=T-273.5;


  Serial.println(T);
delay(500);

}
