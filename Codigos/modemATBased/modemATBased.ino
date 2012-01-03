//#define debug_ModemATBased

#include <ModemATBased.h>

const String host         =  "kemper.com.br";
const String hostPort     =  String ( 80, DEC );
const String queryString  =  "/modem/modem.php?contador=";

unsigned int contadorLoop          =  0;

void setup ()
{
  Serial.begin ( 19200 );
  
  ModemATBased::StateMachineEvent = &Evento;
  ModemATBased::setSerial ( SerialPort::Port1, 19200 );
  
  ModemATBased::Telefon =  "97344690";
  ModemATBased::Message =  ">dado:Hello World! In Brasil, this message can be 128 characters per message";
}

void Evento ( eEvent e, eEvent d )
{
  switch ( e )
  {
    case Event::IdCaptured:             Serial.print ( "\r\nEvento: Id - " );
                                        Serial.println ( ModemATBased::Id );
                                        break;
                                        
    case Event::DayCaptured:            Serial.print ( "\r\nEvento: Day - " );
                                        Serial.println ( ModemATBased::Day );
                                        break;
                                        
    case Event::MonthCaptured:          Serial.print ( "\r\nEvento: Month - " );
                                        Serial.println ( ModemATBased::Month );
                                        break;
                                        
    case Event::YearCaptured:           Serial.print ( "\r\nEvento: Year - " );
                                        Serial.println ( ModemATBased::Year );
                                        break;
                                        
    case Event::HourCaptured:           Serial.print ( "\r\nEvento: Hour - " );
                                        Serial.println ( ModemATBased::Hour );
                                        break;
                                        
    case Event::MinuteCaptured:         Serial.print ( "\r\nEvento: Minute - " );
                                        Serial.println ( ModemATBased::Minute );
                                        break;
                                        
    case Event::SecondCaptured:         Serial.print ( "\r\nEvento: Second - " );
                                        Serial.println ( ModemATBased::Second );
                                        break;
                                        
    case Event::TelefonCaptured:        Serial.print ( "\r\nEvento: Telefon - " );
                                        Serial.println ( ModemATBased::Telefon );
                                        break;
                                        
    case Event::MessageCaptured:        Serial.print ( "\r\nEvento: Message - " );
                                        Serial.println ( ModemATBased::Message );
                                        break;
                                        
    case Event::StatusCaptured:         Serial.print ( "\r\nEvento: Status - " );
                                        Serial.println ( ModemATBased::Status );
                                        break;
                                        
    case Event::CallReady:              Serial.println ( "\r\nEvento: Modem pronto" );
                                        break;
                                        
    case Event::PowerDown:              Serial.println ( "\r\nEvento: Modem desligado" );
                                        break;
                                        
    case Event::SMSSend:                Serial.println ( "\r\nEvento: SMS send" );
                                        break;
                                        
    case Event::SMSNew:                 Serial.println ( "\r\nEvento: Novo SMS\r" );
                                        ModemATBased::readTextSms ();
                                        break;
                                        
    case Event::Ring:                   Serial.println ( "\r\nEvento: tocando\r" ); 
                                        break;
                                        
    case Event::NoCarrier:              Serial.println ( "\r\nEvento: Parou de tocar\r" );
                                        break;
                                        
    case Event::Closed:
    case Event::InternetConnect:        Serial.println ( "\r\nEvento: internet connected" );
                                        ModemATBased::Host        =  "kemper.com.br";
                                        ModemATBased::HostPort    =  "80";
                                        ModemATBased::internetConnectToHost ();
                                        break;
      
    case Event::InternetConnectToHost:
    case Event::InternetDataSendByGET:  Serial.println ( "\r\nEvento: sent data" );
                                        ModemATBased::QueryString =  "/modem/modem.php?status=";
                                        ModemATBased::QueryString.concat ( String ( contadorLoop, DEC ) );
                                        ModemATBased::internetDataSendByGET ();
                                        contadorLoop ++;
                                        break;
      
    case Event::ConnectionFailed:       Serial.println ( "\r\nEvento: connection failed\r" ); 
                                        pisca(); 
                                        break;
    
    case Event::Error:                  Serial.println ( "\r\nEvento: error\r" );
                                        break;
                                        
    case Event::Close:                  Serial.println ( "\r\nEvento: close\r" );
                                        break;
  }
}

void pisca ()
{
  while ( true )
  {
    pinMode ( 13, OUTPUT );
    digitalWrite ( 13, HIGH );
    delay ( 300 );
    digitalWrite ( 13, LOW );
    delay ( 300 );
  }
}

void loop ()
{
  unsigned char data;
  
  if ( Serial.available() )
  {
    data = Serial.read();
    
    if ( ( data == 's' ) || ( data == 'S' ) )
    {
      ModemATBased::sendTextSms ();
    }
    
    else if ( ( data == 'i' ) || ( data == 'I' ) )
    {
      ModemATBased::internetConnect ();
    }
  }
  
  ModemATBased::getDataModem ();
}