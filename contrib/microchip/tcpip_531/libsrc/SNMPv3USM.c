
#include "TCPIPConfig.h"

#if defined(STACK_USE_SNMPV3_SERVER)
#include "GenericTypeDefs.h"
#include "TCPIP_Stack/SNMP.h"
#include "TCPIP_Stack/SNMPv3.h"
#include "TCPIP_Stack/StackTsk.h"
#include "TCPIP_Stack/Tick.h"
#include "TCPIP_Stack/TCPIP.h"
#include "TCPIP_Stack/Hashes.h"
#include "Crypto/AES.h"

UINT8 md5LocalizedAuthKey[16];
UINT8 sha1LocalizedAuthKey[20];
UINT8 hmacAuthKeyBuf[64];
UINT8 authKey_iPad[64];
UINT8 authKey_oPad[64];
UINT8 HmacMd5Digest[16];
UINT8 HmacSHADigest[20];

UINT8 ivEncrptKeyOut[16];
UINT8 deciphered_text[16];
UINT8 cipher_text[16];
UINT8 snmpV3AesEncryptInitVector[16];//128 Bit
UINT8 snmpV3AesDecryptInitVector[16];//128 Bit
snmpV3EngnUserDataBase snmpV3UserDataBase[SNMPV3_USM_MAX_USER];


	
AES_SESSION_KEY_128_BIT    session_key;

extern UINT8 snmpInMsgAuthParamStrng[];
extern UINT8 snmpOutMsgAuthParamStrng[];
extern UINT8 snmpOutMsgPrvParamStrng[];
extern UINT8 snmpInMsgPrvParamStrng[];
extern UINT8 snmpOutMsgAuthParamLen;
extern UINT8 snmpInMsgAuthParamLen;
extern DWORD_VAL authoritativeSnmpEngineBoots;
extern DWORD_VAL authoritativeSnmpEngineTime;
extern WORD gSnmpv3UserDBIndex; 

extern SNMPV3MSGDATA gSNMPv3TrapMsgHeaderBuf;

void Snmpv3Pswd2LocalizedAuthKeyMD5Hashing(UINT8* pswdToLocalized, UINT8 pswdLen);
void Snmpv3Pswd2LocalizedAuthKeySHAHashing(UINT8* pswdToLocalized, UINT8 pswdLen);
void Snmpv3UsmSnmpEngnAuthPrivPswdLocalization(UINT8 userDBIndex);
void Snmpv3InitializeUserDataBase(void);
void Snmpv3ComputeMd5HmacCode(UINT8 xx_bits,UINT8* digestptr,UINT8 * indata, UINT32 dataLen,
					  UINT8* userExtendedLclzdKeyIpad, UINT8* userExtendedLclzdKeyOpad);
void Snmpv3ComputeShaHmacCode(UINT8 xx_bits,UINT8* digestptr, UINT8 * indata, UINT32 dataLen,
					 UINT8* userExtendedLclzdKeyIpad,UINT8* userExtendedLclzdKeyOpad);
void Snmpv3AuthKeyZeroing2HmacBufLen64(UINT8* authKey, UINT8 authKeyLen,	UINT8 hashType);
UINT8* Snmpv3ComputeHmacMD5Digest(UINT8 * inData, UINT32 dataLen,UINT8* userExtendedLclzdKeyIpad,UINT8* userExtendedLclzdKeyOpad);
UINT8* Snmpv3ComputeHmacShaDigest(UINT8 * inData, UINT32 dataLen,UINT8* userExtendedLclzdKeyIpad,UINT8* userExtendedLclzdKeyOpad);

extern void Snmpv3AuthKeyZeroing2HmacBufLen64(UINT8* authKey, UINT8 authKeyLen,  UINT8 hashType);




void Snmpv3InitializeUserDataBase(void)
{
UINT8 userDBIndex=0;
		memset(snmpV3UserDataBase,0,sizeof(snmpV3UserDataBase));

		memcpy(snmpV3UserDataBase[userDBIndex].userName,"microchip",strlen("microchip"));
		snmpV3UserDataBase[userDBIndex].userNameLength=strlen("microchip");
		memcpy(snmpV3UserDataBase[userDBIndex].userAuthPswd,"auth12345",strlen("auth12345"));
		snmpV3UserDataBase[userDBIndex].userAuthPswdLen=0x09;
		memcpy(snmpV3UserDataBase[userDBIndex].userPrivPswd,"priv12345",strlen("priv12345"));
		snmpV3UserDataBase[userDBIndex].userPrivPswdLen=0x09;
		snmpV3UserDataBase[userDBIndex].userHashType=SNMPV3_HAMC_MD5;
		snmpV3UserDataBase[userDBIndex].userPrivType=SNMPV3_AES_PRIV;
		snmpV3UserDataBase[userDBIndex].userDBIndex=userDBIndex;

		userDBIndex+=1;
		memcpy(snmpV3UserDataBase[userDBIndex].userName,"SnmpAdmin",strlen("SnmpAdmin"));
		snmpV3UserDataBase[userDBIndex].userNameLength=strlen("SnmpAdmin");
		memcpy(snmpV3UserDataBase[userDBIndex].userAuthPswd,"ChandlerUS",strlen("ChandlerUS"));
		snmpV3UserDataBase[userDBIndex].userAuthPswdLen=0x0a;
		memcpy(snmpV3UserDataBase[userDBIndex].userPrivPswd,"arizonaUSA",strlen("arizonaUSA"));
		snmpV3UserDataBase[userDBIndex].userPrivPswdLen=0x0a;
		snmpV3UserDataBase[userDBIndex].userHashType=SNMPV3_HMAC_SHA1;
		snmpV3UserDataBase[userDBIndex].userPrivType=SNMPV3_NO_PRIV;
		snmpV3UserDataBase[userDBIndex].userDBIndex=userDBIndex;
		
		userDBIndex+=1;
		memcpy(snmpV3UserDataBase[userDBIndex].userName,"root",strlen("root"));
		snmpV3UserDataBase[userDBIndex].userNameLength=strlen("root");
		memcpy(snmpV3UserDataBase[userDBIndex].userAuthPswd,"authAdmin",strlen("authAdmin"));
		snmpV3UserDataBase[userDBIndex].userAuthPswdLen=0x09;
		memcpy(snmpV3UserDataBase[userDBIndex].userPrivPswd,"privAdmin",strlen("privAdmin"));
		snmpV3UserDataBase[userDBIndex].userPrivPswdLen=0x09;
		snmpV3UserDataBase[userDBIndex].userHashType=SNMPV3_NO_HMAC_AUTH;
		snmpV3UserDataBase[userDBIndex].userPrivType=SNMPV3_NO_PRIV;
		snmpV3UserDataBase[userDBIndex].userDBIndex=userDBIndex;

}


//RFC3826
void Snmpv3UsmAesEncryptDecryptInitVector(BYTE inOutPdu)
{
	BYTE j;
	UINT8* decryptPtr;
	UINT8* prvParamPtr;
	
	if(inOutPdu== SNMP_REQUEST_PDU) //init vector for decryption
	{

		prvParamPtr=snmpInMsgPrvParamStrng;
		decryptPtr= snmpV3AesDecryptInitVector;
		
		//RFC 3826 section 3.1.2.1 Page #7
		//snmpV3AesDecryptInitVector=AuthSnmpEngnBoots+AuthSnmpEngnTime+inMsgPrivParam;
		*decryptPtr++=authoritativeSnmpEngineBoots.v[3];
		*decryptPtr++=authoritativeSnmpEngineBoots.v[2];
		*decryptPtr++=authoritativeSnmpEngineBoots.v[1];
		*decryptPtr++=authoritativeSnmpEngineBoots.v[0];

		*decryptPtr++=authoritativeSnmpEngineTime.v[3];
		*decryptPtr++=authoritativeSnmpEngineTime.v[2];
		*decryptPtr++=authoritativeSnmpEngineTime.v[1];
		*decryptPtr++=authoritativeSnmpEngineTime.v[0];

		j=0;
		while(1)
		{
			*decryptPtr++=*(prvParamPtr+j);
			if(j==7)
				break;
			j++;
		}	

	}
	else if(inOutPdu == SNMP_RESPONSE_PDU) //init vector for encryption
	{

		prvParamPtr=snmpOutMsgPrvParamStrng;
		decryptPtr= snmpV3AesEncryptInitVector;
		
		*decryptPtr++=authoritativeSnmpEngineBoots.v[3];
		*decryptPtr++=authoritativeSnmpEngineBoots.v[2];
		*decryptPtr++=authoritativeSnmpEngineBoots.v[1];
		*decryptPtr++=authoritativeSnmpEngineBoots.v[0];

		*decryptPtr++=snmpEngineTime.v[3];
		*decryptPtr++=snmpEngineTime.v[2];
		*decryptPtr++=snmpEngineTime.v[1];
		*decryptPtr++=snmpEngineTime.v[0];

		j=0;
		while(1)
		{
			*decryptPtr++=*(prvParamPtr+j);
			if(j==7)
				break;
			j++;
		}

	}
}

void Snmpv3USMOutMsgPrivParam(void)
{
	UINT8* prvParamPtr;

	//SNMP ENgine Time is 32 Bit counter. 64 Bit counter (Extended Data type) to be implemented.
	Snmpv3GetAuthEngineTime();

	prvParamPtr=snmpOutMsgPrvParamStrng;	
	
	*prvParamPtr++=0x00;
	*prvParamPtr++=0x00;
	*prvParamPtr++=0x00;
	*prvParamPtr++=0x00;

	//ORing is done to generate some random number from the snmp engine time rand() not used. 
	*prvParamPtr++=snmpEngineTime.v[3]^0xFF;
	*prvParamPtr++=snmpEngineTime.v[2]^0xEE;
	*prvParamPtr++=snmpEngineTime.v[1]^0xDD;
	*prvParamPtr++=snmpEngineTime.v[0]^0xCC;
	
}


void Snmpv3UsmOutMsgAuthenticationParam(UINT8 hashType)
{
	if(hashType == SNMPV3_HAMC_MD5)
	{
		Snmpv3ComputeMd5HmacCode(96,snmpOutMsgAuthParamStrng,(UINT8*)gSNMPv3TrapMsgHeaderBuf.head,
			gSNMPv3TrapMsgHeaderBuf.length,
				snmpV3UserDataBase[0].userAuthLocalKeyHmacIpad,snmpV3UserDataBase[0].userAuthLocalKeyHmacOpad);
	}
	else if(hashType == SNMPV3_HMAC_SHA1)
	{
		Snmpv3ComputeShaHmacCode(96,snmpOutMsgAuthParamStrng,(UINT8*)gSNMPv3TrapMsgHeaderBuf.head,
			gSNMPv3TrapMsgHeaderBuf.length,
				snmpV3UserDataBase[0].userAuthLocalKeyHmacIpad,snmpV3UserDataBase[0].userAuthLocalKeyHmacOpad);

	}
}



void Snmpv3UsmSnmpEngnAuthPrivPswdLocalization(UINT8 userDBIndex)
{
	if(snmpV3UserDataBase[userDBIndex].userHashType== SNMPV3_HAMC_MD5)
	{
		Snmpv3Pswd2LocalizedAuthKeyMD5Hashing(snmpV3UserDataBase[userDBIndex].userAuthPswd,
											snmpV3UserDataBase[userDBIndex].userAuthPswdLen);
		memcpy(snmpV3UserDataBase[userDBIndex].userAuthPswdLoclizdKey,md5LocalizedAuthKey,16);

		if((snmpV3UserDataBase[userDBIndex].userPrivPswdLen != 0x00)&& 
	   (snmpV3UserDataBase[userDBIndex].userPrivType == SNMPV3_AES_PRIV))
	{
		Snmpv3Pswd2LocalizedAuthKeyMD5Hashing(snmpV3UserDataBase[userDBIndex].userPrivPswd,
											snmpV3UserDataBase[userDBIndex].userPrivPswdLen);

		memcpy(snmpV3UserDataBase[userDBIndex].userPrivPswdLoclizdKey,md5LocalizedAuthKey,16);	
	}
	}
	else if(snmpV3UserDataBase[userDBIndex].userHashType == SNMPV3_HMAC_SHA1)
	{
		Snmpv3Pswd2LocalizedAuthKeySHAHashing(snmpV3UserDataBase[userDBIndex].userAuthPswd,
											snmpV3UserDataBase[userDBIndex].userAuthPswdLen);
		memcpy(snmpV3UserDataBase[userDBIndex].userAuthPswdLoclizdKey,sha1LocalizedAuthKey,20);

		if((snmpV3UserDataBase[userDBIndex].userPrivPswdLen != 0x00)&& 
	   (snmpV3UserDataBase[userDBIndex].userPrivType == SNMPV3_AES_PRIV))
	{
		Snmpv3Pswd2LocalizedAuthKeySHAHashing(snmpV3UserDataBase[userDBIndex].userPrivPswd,
											snmpV3UserDataBase[userDBIndex].userPrivPswdLen);

		memcpy(snmpV3UserDataBase[userDBIndex].userPrivPswdLoclizdKey,sha1LocalizedAuthKey,20);	
	}
	}

	/*if((snmpV3UserDataBase[userDBIndex].userPrivPswdLen != 0x00)&& 
	   (snmpV3UserDataBase[userDBIndex].userPrivType == SNMPV3_AES_PRIV))
	{
		Snmpv3Pswd2LocalizedAuthKeyMD5Hashing(snmpV3UserDataBase[userDBIndex].userPrivPswd,
											snmpV3UserDataBase[userDBIndex].userPrivPswdLen);

		memcpy(snmpV3UserDataBase[userDBIndex].userPrivPswdLoclizdKey,md5LocalizedAuthKey,16);	
	}*/
	return;
	
}



void Snmpv3Pswd2LocalizedAuthKeyMD5Hashing(UINT8* pswdToLocalized, UINT8 pswdLen)
{
static HASH_SUM md5;
UINT8 *compressionPtr, pswdBuf[64];
UINT32 index = 0;
UINT32 count = 0, i;
UINT8* pswdPtr;

	pswdPtr=pswdToLocalized;

	MD5Initialize(&md5);
	
	while (count < 1048576)
	{
		compressionPtr = pswdBuf;
		for (i = 0; i < 64; i++) 
		{
			*compressionPtr++ = pswdPtr[index++ % pswdLen];
		}


		MD5AddData(&md5, pswdBuf, 64);
		count+=64;
	
	}
	MD5Calculate(&md5, md5LocalizedAuthKey);

	memcpy(pswdBuf, md5LocalizedAuthKey, 16 /*localizedAuthKey buf len*/);
	memcpy(pswdBuf+16, snmpEngineID, snmpEngnIDLength);
	memcpy(pswdBuf+16+snmpEngnIDLength, md5LocalizedAuthKey, 16 /*localizedAuthKey buf len*/);

	MD5Initialize(&md5);
	MD5AddData(&md5,pswdBuf,32+snmpEngnIDLength);
	
	MD5Calculate(&md5, md5LocalizedAuthKey);

	count+=64;

	return;
}

void Snmpv3Pswd2LocalizedAuthKeySHAHashing(UINT8* pswdToLocalized, UINT8 pswdLen)
{
static HASH_SUM sha1;
UINT8 *compressionPtr, pswdBuf[72];
UINT32 index = 0;
UINT32 count = 0, i;
UINT8* pswdPtr;

	pswdPtr=pswdToLocalized;

	SHA1Initialize(&sha1);
	
	while (count < 1048576)
	{
		compressionPtr = pswdBuf;
		for (i = 0; i < 64; i++) 
		{
			*compressionPtr++ = pswdPtr[index++ % pswdLen];
		}


		SHA1AddData(&sha1, pswdBuf, 64);
		count+=64;
	
	}
	SHA1Calculate(&sha1, sha1LocalizedAuthKey);

	memcpy(pswdBuf, sha1LocalizedAuthKey, 20 /*SHA1 localizedAuthKey buf len*/);
	memcpy(pswdBuf+20, snmpEngineID, snmpEngnIDLength);
	memcpy(pswdBuf+20+snmpEngnIDLength, sha1LocalizedAuthKey, 20 /*SHA1 localizedAuthKey buf len*/);

	SHA1Initialize(&sha1);
	SHA1AddData(&sha1,pswdBuf,40+snmpEngnIDLength);
	
	SHA1Calculate(&sha1, sha1LocalizedAuthKey);

	count+=64;

	return;
}

void Snmpv3ComputeHMACIpadOpadForAuthLoclzedKey(UINT8 userDBIndex)
{
	if(snmpV3UserDataBase[userDBIndex].userHashType==SNMPV3_HAMC_MD5)
	{
		Snmpv3AuthKeyZeroing2HmacBufLen64(snmpV3UserDataBase[userDBIndex].userAuthPswdLoclizdKey,
								16,snmpV3UserDataBase[userDBIndex].userHashType);
	}
	else if(snmpV3UserDataBase[userDBIndex].userHashType==SNMPV3_HMAC_SHA1)
	{
		Snmpv3AuthKeyZeroing2HmacBufLen64(snmpV3UserDataBase[userDBIndex].userAuthPswdLoclizdKey,
								20,snmpV3UserDataBase[userDBIndex].userHashType);
	}
	//authKeyInnerOuterPadding();

	//Authorazation key inner padding
	UINT8 i=0;
	for(i=0;i<64;i++)
		authKey_iPad[i]=hmacAuthKeyBuf[i]^0x36;

	//Authorazation key outer padding
	for(i=0;i<64;i++)
		authKey_oPad[i]=hmacAuthKeyBuf[i]^0x5c;

	memcpy(snmpV3UserDataBase[userDBIndex].userAuthLocalKeyHmacIpad,authKey_iPad,64);
	memcpy(snmpV3UserDataBase[userDBIndex].userAuthLocalKeyHmacOpad,authKey_oPad,64);
}






BYTE Snmpv3AuthenticateRxedPduForDataIntegrity(SNMPV3_REQUEST_WHOLEMSG* rxDataPtr)
{	
UINT8 reportMsgName[7]="initial";//respose is "report" 0xa8 msg
UINT8* secNamePtr;
UINT8 i;
WORD authParamOffset;
UINT8 hashTYpe;
static HASH_SUM md5;
UINT8* tempPtr;

	secNamePtr= securityPrimitivesOfIncomingPdu.securityName;
	hashTYpe=snmpV3UserDataBase[gSnmpv3UserDBIndex].userHashType;

	//Check if the received packet is expecting "report" as response.
	if(!strncmp((const char *)secNamePtr,
				(const char *)reportMsgName,		
				(securityPrimitivesOfIncomingPdu.securityNameLength)))
		return FALSE; //If "report" is expected, Retrun. 

	authParamOffset=gSnmpV3InPduWholeMsgBuf.msgAuthParamOffsetInWholeMsg;

	tempPtr=gSnmpV3InPduWholeMsgBuf.snmpMsgHead;
	for(i=0;i<snmpInMsgAuthParamLen /*Should be 12 Bytes*/;i++)
	{

		//RFC3414 Section 6.3.2 Page#56 Step3
		*(tempPtr+authParamOffset+i)=0x00;
	}

	if(hashTYpe == SNMPV3_HAMC_MD5)
	{

		MD5Initialize(&md5);
		MD5AddData(&md5,snmpV3UserDataBase[gSnmpv3UserDBIndex].userAuthLocalKeyHmacIpad, (WORD)0x40);
		MD5AddData(&md5, rxDataPtr->wholeMsgHead, rxDataPtr->wholeMsgLen.Val);
		MD5Calculate(&md5, HmacMd5Digest);
		
		MD5Initialize(&md5);
		MD5AddData(&md5, snmpV3UserDataBase[gSnmpv3UserDBIndex].userAuthLocalKeyHmacOpad, (WORD)0x40);
		MD5AddData(&md5, HmacMd5Digest,16);
		MD5Calculate(&md5, HmacMd5Digest);

		
	}
	else if(hashTYpe == SNMPV3_HMAC_SHA1)
	{
		SHA1Initialize(&md5);
		SHA1AddData(&md5,snmpV3UserDataBase[gSnmpv3UserDBIndex].userAuthLocalKeyHmacIpad, (WORD)0x40);
		SHA1AddData(&md5, rxDataPtr->wholeMsgHead, rxDataPtr->wholeMsgLen.Val);
		SHA1Calculate(&md5, HmacSHADigest);
		
		SHA1Initialize(&md5);
		SHA1AddData(&md5, snmpV3UserDataBase[gSnmpv3UserDBIndex].userAuthLocalKeyHmacOpad, (WORD)0x40);
		SHA1AddData(&md5, HmacSHADigest,20);
		SHA1Calculate(&md5, HmacSHADigest);
		//return TRUE;
	}
	else
		return SNMPV3_MSG_AUTH_FAIL ;

	if(hashTYpe == SNMPV3_HAMC_MD5)
	{
		i=strncmp((const char *)&snmpInMsgAuthParamStrng,(const char *)&HmacMd5Digest,12);
	}
	else if(hashTYpe == SNMPV3_HMAC_SHA1)
	{
		i=strncmp((const char *)&snmpInMsgAuthParamStrng,(const char *)&HmacSHADigest,12);
	}	
	if(i!=0)
		return SNMPV3_MSG_AUTH_FAIL;

	
	//Authparam validated on WholeMsg. Write back the auth param string to received buffer	
	tempPtr=gSnmpV3InPduWholeMsgBuf.snmpMsgHead;
	for(i=0;i<snmpInMsgAuthParamLen /*Should be 12 Bytes*/;i++)
	{
		*(tempPtr+authParamOffset+i)=snmpInMsgAuthParamStrng[i];
	}

	return SNMPV3_MSG_AUTH_PASS;
		

}


BYTE Snmpv3AuthenticateTxPduForDataIntegrity(SNMPV3_RESPONSE_WHOLEMSG* txDataPtr)
{	
UINT8* secNamePtr;
UINT8 i;
static HASH_SUM md5;
UINT8* tempPtr;
UINT8 hashTYpe;

	hashTYpe=snmpV3UserDataBase[gSnmpv3UserDBIndex].userHashType;	

	if(hashTYpe == SNMPV3_HAMC_MD5)
	{

		MD5Initialize(&md5);
		MD5AddData(&md5,snmpV3UserDataBase[gSnmpv3UserDBIndex].userAuthLocalKeyHmacIpad, (WORD)0x40);
		MD5AddData(&md5, txDataPtr->wholeMsgHead, txDataPtr->wholeMsgLen.Val);
		MD5Calculate(&md5, HmacMd5Digest);
		
		MD5Initialize(&md5);
		MD5AddData(&md5, snmpV3UserDataBase[gSnmpv3UserDBIndex].userAuthLocalKeyHmacOpad, (WORD)0x40);
		MD5AddData(&md5, HmacMd5Digest,16);
		MD5Calculate(&md5, HmacMd5Digest);

		
	}
	else if(hashTYpe == SNMPV3_HMAC_SHA1)
	{
		SHA1Initialize(&md5);
		SHA1AddData(&md5,snmpV3UserDataBase[gSnmpv3UserDBIndex].userAuthLocalKeyHmacIpad, (WORD)0x40);
		SHA1AddData(&md5, txDataPtr->wholeMsgHead, txDataPtr->wholeMsgLen.Val);
		SHA1Calculate(&md5, HmacSHADigest);
		
		SHA1Initialize(&md5);
		SHA1AddData(&md5, snmpV3UserDataBase[gSnmpv3UserDBIndex].userAuthLocalKeyHmacOpad, (WORD)0x40);
		SHA1AddData(&md5, HmacSHADigest,20);
		SHA1Calculate(&md5, HmacSHADigest);
	
	}
	else
		return SNMPV3_MSG_AUTH_FAIL ;

	//Authparam validated on WholeMsg. Write back the auth param string to received buffer	
	tempPtr=snmpOutMsgAuthParamStrng;
	if(hashTYpe == SNMPV3_HAMC_MD5)
		secNamePtr=HmacMd5Digest;
	else if(hashTYpe == SNMPV3_HMAC_SHA1)
		secNamePtr=HmacSHADigest;
		

	i=0;
	for(i=0;i < 12/*snmpOutMsgAuthParamLen Should be 12 Bytes*/;i++)
	{
		tempPtr[i]=secNamePtr[i];
	}
	return SNMPV3_MSG_AUTH_PASS;
}


BYTE Snmpv3AESDecryptRxedScopedPdu(/*UINT8 userDBIndex*/)
{

UINT8* cryptoKey;
UINT8* initVector;
UINT8* cipher_text;
WORD cipherTextLen;
UINT8* decrypted_text;
WORD temp;
BYTE extraMemReqd;

	AES_ROUND_KEYS_128_BIT round_keys;
	AES_CFB_STATE_DATA current_stream;

	cryptoKey=snmpV3UserDataBase[gSnmpv3UserDBIndex].userPrivPswdLoclizdKey;
	initVector=snmpV3AesDecryptInitVector;
	temp=gSnmpV3InPduWholeMsgBuf.scopedPduOffset;
	cipher_text=(gSnmpV3InPduWholeMsgBuf.snmpMsgHead+temp);
	cipherTextLen= gSnmpV3InPduWholeMsgBuf.scopedPduStructLen;

	extraMemReqd=(16-(cipherTextLen%16)); //AES Blocks are in multiples of 16 Bytes
	decrypted_text=(BYTE*)(malloc((size_t)cipherTextLen+extraMemReqd));
	
	if(decrypted_text != NULL)
	{
				
		AESCreateRoundKeys (&round_keys,cryptoKey,AES_KEY_SIZE_128_BIT);
	
		memcpy(current_stream.initial_vector,initVector,16);
	
		AESCFBDecrypt(decrypted_text,cipher_text, cipherTextLen,	
						&round_keys, &current_stream,		 
						AES_STREAM_START | AES_USE_CFB128);
	}
	else
		return SNMPV3_MSG_PRIV_FAIL;

	//Copy decrypted text to already allocated WholeMsg dynamic memory Buffer.
	memcpy(cipher_text,decrypted_text,cipherTextLen);

	//free this temp buffer used for decryption purpose.
	free(decrypted_text);

	return SNMPV3_MSG_PRIV_PASS;
}


BYTE Snmpv3AESEncryptResponseScopedPdu(SNMPV3_RESPONSE_WHOLEMSG* plain_text/*UINT8 userDBIndex*/)
{

UINT8* cryptoKey;
UINT8* initVector;
UINT8* plainText;
WORD plaintextLen;
UINT8* encrypted_text;
BYTE extraMemReqd;
AES_ROUND_KEYS_128_BIT round_keys;
AES_CFB_STATE_DATA current_stream;

		
	//This is a secured request. Compute the AES Encryption IV 
	Snmpv3UsmAesEncryptDecryptInitVector(SNMP_RESPONSE_PDU);

	plaintextLen= (plain_text->scopedPduStructLen);
	cryptoKey=snmpV3UserDataBase[gSnmpv3UserDBIndex].userPrivPswdLoclizdKey;
	initVector=snmpV3AesEncryptInitVector;
	plainText=(plain_text->scopedPduOffset);
	

	extraMemReqd=(16-(plaintextLen%16)); //AES Blocks are in multiples of 16 Bytes
	encrypted_text=(UINT8*)(malloc((size_t)plaintextLen+extraMemReqd));

	if(encrypted_text != NULL)
	{		
		AESCreateRoundKeys (&round_keys,cryptoKey,AES_KEY_SIZE_128_BIT);

        memcpy(current_stream.initial_vector,initVector,16);

		AESCFBEncrypt(encrypted_text,plainText, plaintextLen,    
                    &round_keys, &current_stream,        
                    AES_STREAM_START | AES_USE_CFB128 );

	}
	else
		return	SNMPV3_MSG_PRIV_FAIL;

	//Copy decrypted text to already allocated WholeMsg dynamic memory Buffer.
	memcpy(plainText,encrypted_text,plaintextLen);

	//free this temp buffer used for decryption purpose.
	free(encrypted_text);

	return SNMPV3_MSG_PRIV_PASS;
}


BOOL Snmpv3ValidateEngineId(void)
{
BYTE* inEngnIdPtr=NULL;
BYTE temp;
UINT8 reportMsgName[7]="initial";//respose is "report" 0xa8 msg
UINT8* secNamePtr=NULL;

	secNamePtr= securityPrimitivesOfIncomingPdu.securityName;

	//Check if the received packet is expecting "report" as response.
	if(!strncmp((const char *)secNamePtr,
				(const char *)reportMsgName,		
				(securityPrimitivesOfIncomingPdu.securityNameLength)))
		return TRUE; //If "report" is expected, Retrun. 

	else
	{
	
		inEngnIdPtr=securityPrimitivesOfIncomingPdu.securityEngineID;

		temp=strncmp((const char *)inEngnIdPtr,
					(const char *)snmpEngineID,		
					(securityPrimitivesOfIncomingPdu.securityEngineIDLen));
		if(temp!=0)
			return FALSE; //If "report" is expected, Retrun. 
		else
			return TRUE;
	}
}


BOOL Snmpv3ValidateSecurityName(void)
{
BYTE* inSecNamePtr;
BYTE tempLen,i,temp;
UINT8 reportMsgName[7]="initial";//respose is "report" 0xa8 msg

	tempLen=securityPrimitivesOfIncomingPdu.securityNameLength;
	inSecNamePtr=securityPrimitivesOfIncomingPdu.securityName;

	//Check if the received packet is expecting "report" as response.
	if(!strncmp((const char *)inSecNamePtr,
					(const char *)reportMsgName,		
					tempLen))
	{
			gSnmpv3UserDBIndex=0;
			return TRUE; //If "report" is expected, Retrun. 
	}
	else
	{
		for(i=0;i<SNMPV3_USM_MAX_USER;i++)
		{
			temp=strncmp((const char *)snmpV3UserDataBase[i].userName,
						  (const char *)inSecNamePtr,tempLen);

			if(temp==0)
			{
				gSnmpv3UserDBIndex=i;
				return TRUE;
			}
		}
		gSnmpv3UserDBIndex=0;
	}
	return FALSE;

}

BYTE Snmpv3GetSecurityLevel(BYTE userIndex)
{

	if(((snmpV3UserDataBase[userIndex].userHashType == SNMPV3_HAMC_MD5) || (snmpV3UserDataBase[userIndex].userHashType == SNMPV3_HMAC_SHA1))
	&& ((snmpV3UserDataBase[userIndex].userPrivType == SNMPV3_AES_PRIV) || (snmpV3UserDataBase[userIndex].userPrivType == SNMPV3_DES_PRIV)))
		return NO_REPORT_PRIVACY_AND_AUTH_PROVIDED;
	else if(((snmpV3UserDataBase[userIndex].userHashType == SNMPV3_HAMC_MD5) || (snmpV3UserDataBase[userIndex].userHashType == SNMPV3_HMAC_SHA1))
		&& (snmpV3UserDataBase[userIndex].userPrivType == SNMPV3_NO_PRIV))
		return NO_REPORT_NO_PRIVACY_BUT_AUTH_PROVIDED;
	else
		return NO_REPORT_NO_PRIVACY_NO_AUTH;
	

}

BOOL Snmpv3ValidateSecNameAndSecLvl(void)
{
	BYTE* inSecNamePtr=NULL;
	UINT8 reportMsgName[7]="initial";//respose is "report" 0xa8 msg
	BYTE  tempLen=0,i=0,temp=0;
	BYTE  inSecurityLevel=0;

	
	
	tempLen=securityPrimitivesOfIncomingPdu.securityNameLength;
	if(tempLen == 0x0u)
		return FALSE;

	inSecNamePtr=securityPrimitivesOfIncomingPdu.securityName;
	inSecurityLevel = securityPrimitivesOfIncomingPdu.securityLevel;

	
	if(!strncmp((const char *)inSecNamePtr,
					(const char *)reportMsgName,		
					tempLen))
	{
			gSnmpv3UserDBIndex=0;
			return TRUE; //If "report" is expected, Retrun. 
	}
	else
	{
		for(i=0;i<SNMPV3_USM_MAX_USER;i++)
		{
			if(tempLen != snmpV3UserDataBase[i].userNameLength)
				continue;
			temp=strncmp((const char *)snmpV3UserDataBase[i].userName,
						  (const char *)inSecNamePtr,snmpV3UserDataBase[i].userNameLength);

			if((temp==0) && (Snmpv3GetSecurityLevel(i) == (inSecurityLevel&0x03)))
			{
				gSnmpv3UserDBIndex=i;
				return TRUE;
			}
		}
		gSnmpv3UserDBIndex=0;
	}
	return FALSE;
}



void Snmpv3ComputeMd5HmacCode(UINT8 xx_bits,UINT8* digestptr, 			
					  UINT8 * indata, UINT32 dataLen,
					  UINT8* userExtendedLclzdKeyIpad,
					  UINT8* userExtendedLclzdKeyOpad)
{
UINT8* hmacMd5DigestPtr;
UINT8 i;
UINT8* dataPtr;
dataPtr=indata;

	
	hmacMd5DigestPtr=Snmpv3ComputeHmacMD5Digest(dataPtr, dataLen,userExtendedLclzdKeyOpad,userExtendedLclzdKeyOpad);
	
	for(i=0;i<(xx_bits/8);i++)
	{
		digestptr[i]=*(hmacMd5DigestPtr+i);
	}

}


void Snmpv3ComputeShaHmacCode(UINT8 xx_bits,UINT8* digestptr,
					UINT8 * indata, UINT32 dataLen,
					UINT8* userExtendedLclzdKeyIpad,
					UINT8* userExtendedLclzdKeyOpad)
{
UINT8* hmacSHADigestPtr;
UINT8 i;
UINT8* dataptr;
dataptr=indata;


	hmacSHADigestPtr=Snmpv3ComputeHmacShaDigest(dataptr, dataLen,userExtendedLclzdKeyOpad,userExtendedLclzdKeyOpad);

	for(i=0;i<(xx_bits/8);i++)
	{
		digestptr[i]=*(hmacSHADigestPtr+i);
	}

}



void Snmpv3AuthKeyZeroing2HmacBufLen64(UINT8* authKey, UINT8 authKeyLen,  UINT8 hashType)
{
	UINT8* tempAuthKeyptr;
	UINT8 i;

	
	tempAuthKeyptr = authKey;

	if(authKeyLen > 64)
	{
		if(hashType == SNMPV3_HAMC_MD5)
		{
			//Hash MD5 AuthKey;
			//Zero pad the Auth key;
		}
		else if(hashType == SNMPV3_HMAC_SHA1)
		{
			//Hash SHA AuthKey;
			//Zero pad the Auth key;
		}
	}
	else 
	{
		//ZeroPad Auth Key	
		memcpy((void*) &hmacAuthKeyBuf, (const void *)tempAuthKeyptr, authKeyLen);

		for(i=authKeyLen;i<64;i++)
			hmacAuthKeyBuf[i]=0x00;
	}

}




UINT8* Snmpv3ComputeHmacMD5Digest(UINT8 * inData, UINT32 dataLen,UINT8* userExtendedLclzdKeyIpad,UINT8* userExtendedLclzdKeyOpad)
{
	static HASH_SUM md5;
	UINT8 * data2Hmac;
	
	data2Hmac=inData;
	
	MD5Initialize(&md5);
	MD5AddData(&md5, userExtendedLclzdKeyIpad, (WORD)0x40);
	MD5AddData(&md5, data2Hmac, (WORD)dataLen);
	MD5Calculate(&md5, HmacMd5Digest);


	
	MD5Initialize(&md5);
	MD5AddData(&md5, userExtendedLclzdKeyOpad, (WORD)0x40);
	MD5AddData(&md5, HmacMd5Digest,16);
	MD5Calculate(&md5, HmacMd5Digest);

	return HmacMd5Digest;


}



UINT8* Snmpv3ComputeHmacShaDigest(UINT8 * inData, UINT32 dataLen,UINT8* userExtendedLclzdKeyIpad,UINT8* userExtendedLclzdKeyOpad)
{	
	
	static HASH_SUM sha1;
	UINT8 * data2Hmac;
	
	data2Hmac=inData;
	
	SHA1Initialize(&sha1);
	SHA1AddData(&sha1, authKey_iPad, (WORD)0x40);
	SHA1AddData(&sha1, data2Hmac, (WORD)dataLen);
	SHA1Calculate(&sha1, HmacSHADigest);


	
	SHA1Initialize(&sha1);
	SHA1AddData(&sha1, authKey_oPad, (WORD)0x40);
	SHA1AddData(&sha1, HmacSHADigest,20);
	SHA1Calculate(&sha1, HmacSHADigest);

	return HmacSHADigest;
	
}

#endif // #if defined(STACK_USE_SNMPV3_SERVER)
