#include "read_options.h"
#include <glog/logging.h>

int main(int argc, char **argv)
{
	// if(!google::IsGoogleLoggingInitialized())
		// google::InitGoogleLogging("/dev/nell");
	char *fileName = const_cast<char*>("cfg/test.cfg");

	ReadOptions *rp = new ReadOptions(fileName);
	if(!rp->readPermitted())
		delete rp;
	
	char *val = rp->read("name");
	LOG(INFO) << "name: " << val;
	val = rp->read("age");
	LOG(INFO) << "age: " << std::atoi(val);
	val = rp->read("height");
	LOG(INFO) << "height: " << std::atoi(val);
	val = rp->read("age");
	LOG(INFO) << "age: " << std::atoi(val);
    val = rp->read("email");
    LOG(INFO) << "email: " << val;
    if(rp->matchSuffix(val, "com"))
      LOG(INFO) << "emial has suffix of 'com'";
	
	if(NULL != rp)
	{
		delete rp;
		rp = NULL;
}
  return 0;

}
