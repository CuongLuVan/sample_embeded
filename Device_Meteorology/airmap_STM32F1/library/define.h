

#define    OK 0
#define    NG 1
typedef struct _DataSensorStruct{
		uint8_t start;
		uint8_t light;
    uint16_t temperature;
    uint16_t humidity;
    uint32_t pressure;
    uint32_t verhicle;
}DataSensorStruct;

typedef struct _SampleDataSensorStruct{
    uint32_t temperature;
    uint32_t humidity;
    uint32_t pressure;
    float verhicle;
}SampleDataSensorStruct;


