#pragma once

#include <EMLife/EMLife.h>

#ifndef EMLIFE_EMLEXCEPT_H
#define EMLIFE_EMLEXCEPT_H

#define MSGSIZE 128

enum ErrorCode {
	SUCCESS                       = 0,
	FAILED_TO_SPECIFY_ENDPOINT    = 1,
	FAILED_TO_SPECIFY_ALL_DIAMOND = 2
};


struct Error {
	ErrorCode code;
	char msg[MSGSIZE];
	
	Error(ErrorCode code, const char* msg):
	code(code) {
		strcpy(this->msg, msg);
	}
};
typedef std::list<Error> ErrList;


class ErrorManager {
private:
	ErrList error_list;
	
public:
	inline int PrintAll() {
		int count = 0;
		
		for(Error err: error_list) {
			printf("\033[31m[ERROR] %s\033[0m\n", err.msg);
			count++;
		}
		
		return count;
	}
	
	inline void CreateError(ErrorCode err_code) {
		switch(err_code) {
		case SUCCESS:
			return;
		
		case FAILED_TO_SPECIFY_ENDPOINT:
			error_list.emplace_back(
				FAILED_TO_SPECIFY_ENDPOINT,
				"End point cannot be specified because there is no way in the maze."
			);
			break;
			
		case FAILED_TO_SPECIFY_ALL_DIAMOND:
			error_list.emplace_back(
				FAILED_TO_SPECIFY_ALL_DIAMOND,
				"All diamonds cannot be added because the path length is insufficient."
			);
			break;
		}
	}
};
#endif //EMLIFE_EMLEXCEPT_H
