#ifndef __DEBUG_H
#define __DEBUG_H

static class DEBUG
{
	private:
		int errorCode;
		char errorMessage[200];
	public:
		int getLastErrorCode();
		const char* getLastErrorMessage();
		void toLog(int code, const char* msg, ...);
} debug;

#endif