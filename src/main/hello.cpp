#include "hello_cl.h"


#include "android_opencl/OclPlatform.h"
#include "android_opencl/OclLib.h"
#include "android_opencl/Log.h"

#define TAG "Hello "
using cl_context = struct _cl_context *;
#define MEM_SIZE 128
int main()
{
	cl_int ret = 0;
	char string[MEM_SIZE];
	aocl::Log::setVerbose(aocl::Log::Level::DEBUG);
	 if (!aocl::OclLib::init(nullptr)) {
           LOG_ERR( " (failed to load OpenCL runtime)");
	    return -1;
        }
	const auto platforms = aocl::OclPlatform::get();
    if (platforms.empty()) {
	LOG_ERR( "platforms is empty");
        return -2;
    }
	aocl::OclPlatform::print();
	aocl::OclPlatform platform = platforms[0];
	std::vector<aocl::OclDevice> devices = platform.devices();
	aocl::OclDevice  device = devices[0];
	std::vector<cl_device_id> ids = { device.id() };
        cl_context m_ctx = aocl::OclLib::createContext(ids);
	cl_command_queue command_queue = NULL;
	cl_mem memobj = NULL;
	cl_program program = NULL;
	cl_kernel kernel = NULL;
	cl_device_id device_id = device.id();
	command_queue = aocl::OclLib::createCommandQueue(m_ctx, device.id());
	
    	memobj = aocl::OclLib::createBuffer(m_ctx, CL_MEM_READ_WRITE, sizeof(char) * MEM_SIZE);
	/* Create Kernel Program from the source */
	const char *source  = (const char *)hello_cl;
	program = aocl::OclLib::createProgramWithSource(m_ctx, 1, (const char **)&source,nullptr, &ret);
 	LOG_INFO(TAG " compile program ..");
	/* Build Kernel Program */
	ret = aocl::OclLib::buildProgram(program, 1, &device_id, NULL, NULL, NULL);
	 LOG_INFO(TAG " compile done");
	/* Create OpenCL Kernel */
	kernel = aocl::OclLib::createKernel(program, "hello", &ret);
	 
	/* Set OpenCL Kernel Parameters */
	ret = aocl::OclLib::setKernelArg(kernel, 0, sizeof(cl_mem), (void *)&memobj);
	 
	/* Execute OpenCL Kernel */
	const size_t  work_dim = 1;
	const size_t global_work_size = 1;
	
	const size_t local_work_size = 1;
	//const size_t global_work_offset = 0;
	
	ret = aocl::OclLib::enqueueNDRangeKernel(command_queue, kernel, work_dim,nullptr, &global_work_size,&local_work_size, 0,NULL,NULL);
	/* Copy results from the memory buffer */
	ret = aocl::OclLib::enqueueReadBuffer(command_queue, memobj, CL_TRUE, 0,MEM_SIZE * sizeof(char),string, 0, NULL, NULL);
	 LOG_INFO(TAG "Read back string: %s",string);
	 printf("%s\n",string);
	aocl::OclLib::release(m_ctx);
}
