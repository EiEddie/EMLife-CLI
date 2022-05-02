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
		
		fflush(stdout);
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


struct Warning {
	char msg[MSGSIZE];
	
	Warning(const char* msg) {
		strcpy(this->msg, msg);
	}
};
typedef std::list<Warning> WrnList;


extern class WarningManager {
private:
	WrnList warning_list;
	
public:
	inline int PrintAll() {
		int count = 0;
		
		for(Warning wrn: warning_list) {
			printf("\033[33m[WARNING] %s\033[0m\n", wrn.msg);
			count++;
		}
		
		fflush(stdout);
		return count;
	}
	
	inline void CreateFailedToSpecifyAllCoin(int coin_count) {
		char buf[MSGSIZE];
		snprintf(
			buf, MSGSIZE,
			"Only %d coins can be added because the path length is insufficient.",
			coin_count
		);
		warning_list.emplace_back(buf);
	}
} warning_manager;
#endif //EMLIFE_EMLEXCEPT_H
