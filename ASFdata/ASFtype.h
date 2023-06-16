#pragma once
// Header 파일 따로 등록 (mapData.h)

typedef char				S08;		// 1  byte : -128						-> 127
typedef unsigned char		U08;		// 1  byte : 0							-> 255
typedef short				S16;		// 2  byte : -32,768					-> 32,767
typedef unsigned short		U16;		// 2  byte : 0							-> 65,536
typedef int					B32;		// 4  byte : -2,147,483,648				-> 2,147,483,647
typedef B32					S32;		// 4  byte : -2,147,483,648				-> 2,147,483,647
typedef unsigned int		U32;		// 4  byte : 0							-> 4,294,967,295
typedef __int64				S64;		// 4  byte : -9,223,372,036,854,775,807 -> 9,223,372,036,854,775,807
typedef unsigned __int64	U64;		// 4  byte : 0							-> 18,446,744,067,709,551,614
typedef float				F32;		// 4  byte : 1.2e-38					-> 3.4e38
typedef double				F64;		// 8  byte : 2.2e-308					-> 1.8e308
typedef int					B32;		// 4  byte : -2,147,483,648				-> 2,147,483,647



#define MAP_MAX_CH      3
#define MAP_TPG_CH		MAP_MAX_CH-1
#define MAP_MAX_PROG	10          // 최대 호출 프로그램 개수(Main P/G 포함)
#define MAX_AXIS_SIZE   30
#define MAX_MACHINE     30

#define MAX_PATH_SIZE   400				// 300
#define MAX_FILE_SIZE   200				// 50

// maximum axis for IPO
#define MAP_MAX_AXIS    32


// maximum MAP
#define MAP_MAX_X       256         // X MAP
#define MAP_MAX_Y       256         // Y MAP
#define MAP_MAX_T       512         // T MAP
#define MAP_MAX_C       512         // C MAP
#define MAP_MAX_D       4096        // D MAP
#define MAP_MAX_SR      1024        // system memory R MAP
#define MAP_MAX_BR      1024        // battery backup memory R MAP
#define MAP_MAX_G       1000        // G MAP
#define MAP_MAX_F       1000        // F MAP
#define MAP_MAX_PA      11000   // PA MAP
#define MAP_MAX_PI      500         // PI MAP
#define MAP_MAX_PM      10000       // PM MAP
#define MAP_MAX_PP      2000        // PP MAP
#define MAP_MAX_PU      11000        // PU MAP
#define MAP_MAX_PS      800         // PS MAP
#define MAP_MAX_SV      2000        // SV MAP
#define MAP_MAX_SN      1000        // SN MAP
#define MAP_MAX_ML      100         // ML MAP
#define MAP_MAX_MGV     100         // MGV MAP
#define MAP_MAX_MGN     500         // MGN MAP
#define MAP_MAX_B       3000        // B MAP