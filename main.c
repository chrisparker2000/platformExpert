#include <CoreFoundation/CoreFoundation.h>
#include <IOKit/IOKitLib.h>


int main (int argc, const char * argv[]) {
	CFDataRef data;
	
    char * arg;
    if (argc == 1)
    {
        char *c_msg = "Called without arguments, looking up serial-number";
        CFStringRef cf_msg = CFStringCreateWithCString(0, c_msg, kCFStringEncodingUTF8);
        CFShow(cf_msg);
        
        arg = "serial-number";
    }
    else
    {
        arg = (char *) argv[1];
    }
    
	io_service_t platformExpert = IOServiceGetMatchingService(kIOMasterPortDefault, IOServiceMatching("IOPlatformExpertDevice"));
	if (platformExpert)
	{
		data = IORegistryEntryCreateCFProperty(platformExpert,
											   CFStringCreateWithCString(
																		 NULL,
																		 arg,
																		 kCFStringEncodingUTF8),
											   kCFAllocatorDefault, 0);
	}
	
	IOObjectRelease(platformExpert);
	CFIndex bufferLength = CFDataGetLength(data);  
	UInt8 *buffer = malloc(bufferLength);
	CFDataGetBytes(data, CFRangeMake(0,bufferLength), (UInt8*) buffer);
	CFStringRef string = CFStringCreateWithBytes(kCFAllocatorDefault,
												 buffer,
												 bufferLength,
												 kCFStringEncodingUTF8,
												 TRUE);
	CFShow(string);
	return 0;
	
}
