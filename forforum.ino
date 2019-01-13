#include <WiFi.h>
#include "time.h"
String time_str;
const char* ssid     = "WiFiFietsie";
const char* password = "576497!MaJeKje";


void setup() { 
  Serial.begin(115200);
  Start_WiFi(ssid,password);
  configTime(0, 0, "pool.ntp.org");
  delay (4000);   // give configtime some time
    setenv("TZ", "CET-1CEST,M3.5.0,M10.5.0/3",1);  //  voor Amsterdam
  stop_wifi(); 
 }
 
void loop() { 
printLocalTime();
delay(4000);
} 

void printLocalTime(){
char *months[] = {"month_0","Januari",   "Februari",  "Maart",    "April",  //januar, februar, etc.
                 "Mei",       "Juni"    ,  "Juli" ,    "Augustus",          //month_0 wil never be printed
			     "September", "October" ,  "November", "December"} ;        // because januar comes as 1
char *days[] = {"Zondag", "Maandag", "Dinsdag", "Woensdag", // Sunday Monday  etc.
               "Donderdag", "Vrijdag", "Zaterdag"};         // Sunday comes as 0
			   
Serial.println (  days[ weekdaynumber()]) ;
Serial.println (months[monthdaynumber()]) ;
Serial.println(seconds());  // seconds are for quicker checking, but not needed for a calender.
Serial.println();
}

int weekdaynumber() // returns the number of the day of th weekdaynumber as int
{
 struct tm timeinfo;
 if(!getLocalTime(&timeinfo))  { Serial.println("Failed to obtain time"); }
  char output[80];
  int weekdaynr; 
  strftime(output, 80, "%w", &timeinfo); // daynumber of the week    sunday = 0, saturday = 6 
  weekdaynr = atoi(output);
  Serial.print("output weekdaynr = ");
  Serial.println(weekdaynr);
  return (weekdaynr);
}

int monthdaynumber()// returns the number of the month as int
{
 struct tm timeinfo;
if(!getLocalTime(&timeinfo))  { Serial.println("Failed to obtain time"); }
 char output[80]; 
 int monthnr;
 strftime(output, 80, "%m", &timeinfo); // month number     januar = 1, december = 12
 monthnr = atoi(output);
 Serial.print("output monthnr = ");
 Serial.println(monthnr);
 return(monthnr);
}

int seconds()// returns the number of the month as int
{
 struct tm timeinfo;
if(!getLocalTime(&timeinfo))  { Serial.println("Failed to obtain time"); }
 char output[80]; 
 int sec;
strftime(output, 80, "%S", &timeinfo); // Seconds 00 to 61   61 (61 for possebillity of astronomical correction}
sec = atoi(output);
 Serial.print("output seconds = ");
 Serial.println(sec);
 return(sec);
}

int Start_WiFi(const char* ssid, const char* password){
 int connAttempts = 0;
 Serial.println("\r\nConnecting to: "+String(ssid));
 WiFi.begin(ssid, password);
 while (WiFi.status() != WL_CONNECTED ) {
   delay(500);
   Serial.print(".");
   if(connAttempts > 20) {Serial.print("No wifi connection");return -5;}
   connAttempts++; }
   Serial.println(); // to make the next Serial.print on a new line
    return 1; }

void stop_wifi(){ WiFi.disconnect(true);
                   WiFi.mode(WIFI_OFF); }
