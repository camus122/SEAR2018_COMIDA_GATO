void informacionUpdate(String itemSeleccionado){
  if(itemSeleccionado=="3.0"){
    printLcd("Informacion","update");
  }    

  if(itemSeleccionado=="3.1"){   
    printPantallaHora("Comida 1",horaComida1,true);
    printPantallaHora("Comida 2",horaComida2,false);
    delay(3000);
    printPantallaHora("Comida 3",horaComida3,true);
    printPantallaHora("Comida 4",horaComida4,false);
    delay(3000);
    printLcdLine1("Cantidad de");
    printLcdLine2(String("porciones= "+PORCIONES));
    delay(3000);
    resetarNiveles();
   }   
}



void printPantallaHora(String titulo,String hora,bool superior){
   String stringBuffer=String(titulo+"= "+hora);
   if(superior){
      printLcdLine1(stringBuffer);
    }else{
      printLcdLine2(stringBuffer);
    }
      
}


