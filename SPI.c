// =======================================================================
// ROTINAS DE SPI VIA BIT BANGING
// =======================================================================

/// \file SPI.c Rotinas de SPI via Bit Baning.
/// A vers�o atual n�o usa o perif�rico SPI do microcontrolador, mas sim
/// a t�cnica de big banging. MISO, MOSI e SCK podem ser configurados para
/// quaisquer pinos de portas dispon�veis do microcontrolador.
/// Autor: F�bio Crestani
/// �ltima modifica��o: 28/12/2014 

#include <REGx51.h>	
#include "SPI.h"
#include "Serial.h"

/////////////////////////////////////////////////////////////////////////////////
/// DelaySPI.
/// Prop�sito: Implementa delay de at� 255 * 0,5 [micro segundos]<br>
/// Entradas: i define o tempo do delay<br>
/// Sa�das: Nenhuma
///
/// \param [in] i inteiro sem sinal com o tempo de delay (i * 0,5us)
/////////////////////////////////////////////////////////////////////////////////
void DelaySPI(unsigned int i){
	unsigned int j;
	for(j=0;j<i;j++);
}

/////////////////////////////////////////////////////////////////////////////////
/// SetMOSI.
/// Prop�sito: MOSI = 1<br>
/// Entradas: Nenhuma<br>
/// Sa�das: Nenhuma
///
/////////////////////////////////////////////////////////////////////////////////
void SetMOSI(){
	MOSI = 1;
}

/////////////////////////////////////////////////////////////////////////////////
/// ClearMOSI.
/// Prop�sito: MOSI = 0<br>
/// Entradas: Nenhuma<br>
/// Sa�das: Nenhuma
///
/////////////////////////////////////////////////////////////////////////////////
void ClearMOSI(){
	MOSI = 0;
}

/////////////////////////////////////////////////////////////////////////////////
/// SetSCK.
/// Prop�sito: SCK = 1<br>
/// Entradas: Nenhuma<br>
/// Sa�das: Nenhuma
///
/////////////////////////////////////////////////////////////////////////////////
void SetSCK(){
	SCK = 1;
}

/////////////////////////////////////////////////////////////////////////////////
/// ClearSCK.
/// Prop�sito: SCK = 0<br>
/// Entradas: Nenhuma<br>
/// Sa�das: Nenhuma
///
/////////////////////////////////////////////////////////////////////////////////
void ClearSCK(){
	SCK = 0;
}

/////////////////////////////////////////////////////////////////////////////////
/// GetMISO.
/// Prop�sito: Recebe estado do pino MISO<br>
/// Entradas: Nenhuma<br>
/// Sa�das: char com o estado do pino MISO
///
/////////////////////////////////////////////////////////////////////////////////
char GetMISO(){
	char A;
	A = MISO;
	return A;
}

/////////////////////////////////////////////////////////////////////////////////
/// SPIWrite.
/// Prop�sito: Envia um caractere atrav�s do pino MOSI<br>
/// Entradas: char dado, dado que ser� enviado<br>
/// Sa�das: Nenhuma
///
/// \param [in] dado char que ser� enviado atrav�s do pino MOSI
/////////////////////////////////////////////////////////////////////////////////
void SPIWrite(char dado){	  
	int i;
	for(i=7; i>=0; i--){				// para os 8 bits do caractere
		if(dado & (1 << i ))            // faz um AND com uma m�scara 
										// que se move at� percorrer os 8 bits
			SetMOSI();					// seta o pino
		else 						    // ou
			ClearMOSI();				// zera o pino

		DelaySPI(10);					// aguarda e gera pulsos de clock
		SetSCK();                       // para o dispositivo slave SPI
		DelaySPI(10);
		ClearSCK();
		DelaySPI(10);
	}
}

/////////////////////////////////////////////////////////////////////////////////
/// SPIRead.
/// Prop�sito: L� um caractere serializado atrav�s do pino MISO<br>
/// Entradas: Nenhuma<br>
/// Sa�das: char com o caractere lido do pino MISO
///
/////////////////////////////////////////////////////////////////////////////////
char SPIRead(){
	int i, b=0;
	
	for(i=7; i>=0; i--){				  // para os 8 bits do caractere
		SetSCK();						  // gera pulso de clock
		DelaySPI(10);                     // aguarda
		if(GetMISO()) b |= 1 << i ;		  // se o bit for alto, faz um OR
		DelaySPI(10);                     // l�gico e seta o bit do resultado
		ClearSCK();						  // mais um pulso de clock
		DelaySPI(10);					  // aguarda
	}	
return b;
}