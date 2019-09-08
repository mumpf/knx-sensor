#define MANUFACTURER_ID 57005
#define DEVICE_ID 1
#define REVISION 3

#define COMOBJ_null 0
#define COMOBJ_null 1
#define COMOBJ_null 2
#define COMOBJ_null 3
#define COMOBJ_null 4
#define PARAM_null 0
#define PARAM_null 1
#define PARAM_null 2
#define PARAM_null 3
#define PARAM_null 4
        
KnxComObject KnxDevice::_comObjectsList[] = {
    /* Index 0 - null */ KnxComObject(KNX_DPT_9_001, 0x34),
    /* Index 1 - null */ KnxComObject(KNX_DPT_9_001, 0x34),
    /* Index 2 - null */ KnxComObject(KNX_DPT_9_008, 0x34),
    /* Index 3 - null */ KnxComObject(KNX_DPT_9_008, 0x34),
    /* Index 4 - null */ KnxComObject(KNX_DPT_9_001, 0x34)
};
const byte KnxDevice::_numberOfComObjects = sizeof (_comObjectsList) / sizeof (KnxComObject); // do not change this code
       
byte KonnektingDevice::_paramSizeList[] = {
    /* Index 0 - null */ PARAM_UINT8,
    /* Index 1 - null */ PARAM_UINT8,
    /* Index 2 - null */ PARAM_UINT8,
    /* Index 3 - null */ PARAM_UINT8,
    /* Index 4 - null */ PARAM_UINT8
};
const byte KonnektingDevice::_numberOfParams = sizeof (_paramSizeList); // do not change this code
