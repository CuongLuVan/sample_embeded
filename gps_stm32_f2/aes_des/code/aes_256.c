
  #include "stm32f4xx.h"
  #include "stm32f4xx_rtc.h"
#include "lcd_320x240.h"

#define AES_TEXT_SIZE    64 /* 16 x 4 */
#define ECB              1
#define CBC              2
#define CTR              3
 uint8_t AES256key[32] = {0x60,0x3d,0xeb,0x10,0x15,0xca,0x71,0xbe,
                          0x2b,0x73,0xae,0xf0,0x85,0x7d,0x77,0x81,
                          0x1f,0x35,0x2c,0x07,0x3b,0x61,0x08,0xd7,
                          0x2d,0x98,0x10,0xa3,0x09,0x14,0xdf,0xf4}; /* key size 256 bytes */
char add[]="you are be alonekjvc  vcnvlkclv vcvckvlkcvkck b cvcvcvvcfdbfdbdbdfbdbj gfgf  bckv nlvc nkvc lvk ck kblk blvb  llbv bcfhjdkflv vb bv b vvb  vb vb kvbk b,v, v,b, ,b bkbk";

uint8_t Plaintext[AES_TEXT_SIZE] = 
                        {0x6b,0xc1,0xbe,0xe2,0x2e,0x40,0x9f,0x96,
                         0xe9,0x3d,0x7e,0x11,0x73,0x93,0x17,0x2a,
                         0xae,0x2d,0x8a,0x57,0x1e,0x03,0xac,0x9c,
                         0x9e,0xb7,0x6f,0xac,0x45,0xaf,0x8e,0x51,
                         0x30,0xc8,0x1c,0x46,0xa3,0x5c,0xe4,0x11,
                         0xe5,0xfb,0xc1,0x19,0x1a,0x0a,0x52,0xef,
                         0xf6,0x9f,0x24,0x45,0xdf,0x4f,0x9b,0x17,
                         0xad,0x2b,0x41,0x7b,0xe6,0x6c,0x37,0x10}; /* plaintext */

uint8_t Ciphertext[AES_TEXT_SIZE] = 
                        {0x76,0x49,0xab,0xac,0x81,0x19,0xb2,0x46,
                         0xce,0xe9,0x8e,0x9b,0x12,0xe9,0x19,0x7d,
                         0x50,0x86,0xcb,0x9b,0x50,0x72,0x19,0xee,
                         0x95,0xdb,0x11,0x3a,0x91,0x76,0x78,0xb2,
                         0x73,0xbe,0xd6,0xb8,0xe3,0xc1,0x74,0x3b,
                         0x71,0x16,0xe6,0x9e,0x22,0x22,0x95,0x16,
                         0x3f,0xf1,0xca,0xa1,0x68,0x1f,0xac,0x09,
                         0x12,0x0e,0xca,0x30,0x75,0x86,0xe1,0xa7}; /* ciphertext */

 uint8_t IV_1[16] = {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,
                     0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f}; 												 
												 
uint8_t Encryptedtext[AES_TEXT_SIZE]; /* Encrypted text */
uint8_t Decryptedtext[AES_TEXT_SIZE]; /* Decrypted text */

void 	Display_EncryptedData(int a,int b,int c){
//display_tex_theododai(a,64,Encryptedtext);
display_text(64,Encryptedtext);	
}
void Display_DecryptedData(int a,int b,int c){
//display_tex_theododai(a,64,Decryptedtext);
display_text(64,Decryptedtext);	
}										 
										 

void mahoa(int t){
	
display_tex_theododai(1,64,add);	
display_text(64,Plaintext);	
/******************************************************************************/
/*                             AES mode ECB                                   */
/******************************************************************************/

/*=====================================================
  Encryption ECB mode                                        
======================================================*/
	_delay_ms(10000);
	/****************************************/
/*                           AES 256   **/
/****************************************/
    /* Encrypt the plaintext message*/
print1("ma thu 1",10,20,0);	
    if(CRYP_AES_ECB(MODE_ENCRYPT,AES256key,256,Plaintext,AES_TEXT_SIZE,Encryptedtext) == SUCCESS);
    {
      /* Display encrypted Data*/
      Display_EncryptedData(ECB, 256,AES_TEXT_SIZE);
    }
			_delay_ms(20000);
/*=====================================================
    Decryption in ECB mode                                       
======================================================*/
		
/****************************************/
/*                           AES 256   **/
/****************************************/
print1("ma thu 2",10,20,0);
    /* Decrypt the plaintext message  */
    if(CRYP_AES_ECB(MODE_DECRYPT,AES256key, 256,Ciphertext, AES_TEXT_SIZE,Decryptedtext) == SUCCESS)
    {
      /* Display decrypted data*/
      Display_DecryptedData(ECB,256,AES_TEXT_SIZE);
    }
	_delay_ms(10000);
/******************************************************************************/
/*                             AES mode CBC                                   */
/******************************************************************************/
/****************************************/
/*                           AES 256   **/
/****************************************/
    /* Encrypt the plaintext message*/
		print1("ma thu 3",10,20,0);
    if(CRYP_AES_CBC(MODE_ENCRYPT,IV_1,AES256key,256,Plaintext,AES_TEXT_SIZE,Encryptedtext) == SUCCESS)
    {
      /* Display encrypted Data*/
      Display_EncryptedData(CBC, 256,AES_TEXT_SIZE);
    }
			_delay_ms(10000);
/*=====================================================
    Decryption in CBC mode                                       
======================================================*/
 /* Deinitializes the CRYP peripheral */
   // CRYP_DeInit();
		/****************************************/
/*                           AES 256   **/
/****************************************/
    /* Deinitializes the CRYP peripheral */
print1("ma thu 4",10,20,0);
    /* Decrypt the plaintext message  */
    if(CRYP_AES_CBC(MODE_DECRYPT,IV_1,AES256key, 256,Ciphertext, AES_TEXT_SIZE,Decryptedtext) == SUCCESS)
    {
      /* Display decrypted data*/
      Display_DecryptedData(CBC,256,AES_TEXT_SIZE);
    }
	_delay_ms(10000);
/******************************************************************************/
/*                             AES mode CTR                                   */
/******************************************************************************/

/*=====================================================
  Encryption CTR mode                                        
======================================================*/
/****************************************/
/*                           AES 256   **/
/****************************************/
    /* Encrypt the plaintext message*/
		print1("ma thu 5",10,20,0);
    if(CRYP_AES_CTR(MODE_ENCRYPT,IV_1,AES256key,256,Plaintext,AES_TEXT_SIZE,Encryptedtext) == SUCCESS)
    {
      /* Display encrypted Data*/
      Display_EncryptedData(CTR, 256, AES_TEXT_SIZE);
    }
			_delay_ms(10000);
/*=====================================================
    Decryption in CTR mode                                       
======================================================*/
/****************************************/
/*                           AES 256   **/
/****************************************/
    /* Decrypt the plaintext message  */
		print1("ma thu 6",10,20,0);
    if(CRYP_AES_CTR(MODE_DECRYPT,IV_1,AES256key, 256,Ciphertext, AES_TEXT_SIZE,Decryptedtext) == SUCCESS)
    {
      /* Display decrypted data*/
      Display_DecryptedData(CTR, 256, AES_TEXT_SIZE);
    }
/******************************************************************************/		

		_delay_ms(10000);	
		

}