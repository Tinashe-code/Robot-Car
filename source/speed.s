// Assembly language code for check key function
//Assembly code for speed control function

	MOVS R0, #0           //Assigning a value to potVal, the value reading ADC
	MOVS R1, #0           //Assignment the speed value
speed_control:
	CMP R0, 0             //Compare potVal with 10
	BLT  Bproceed         //Jump if potVal less than 0
	CMP R0, #4681        //Compare R0 with 4681
	BGT  Bproceed        //Jump if potVal greater than 10
	MOVS R0, #0          //Assigning speed a value of 0
	RET                  //Returning the speed value
proceed:
	MOVS R0, #2000
	CMP R0, #4682          //Compare potVal with 4682
	BLT  Bproceed1        //Jump if potVal less than 4682
	CMP R0, #9362        //Compare R0 with 9362
	BGT  Bproceed1        //Jump if potVal greater than 9362
	MOVS R0, #1          //Assigning speed a value of 1
	RET                  //Returning the speed value
proceed1:
	MOVS R0, #8000
	CMP R0, #9363          //Compare potVal with 9363
	BLT  Bproceed2        //Jump if potVal less than 9363
	CMP R0, #18724        //Compare R0 with 4681
	BGT  Bproceed        //Jump if potVal less than 10
	MOVS R0, #2          //Assigning speed a value of 0
	RET                  //Returning the speed value
proceed2:
	MOVS R0, #19000
	CMP R0, #18724          //Compare potVal with 18724
	BLT  Bproceed3        //Jump if potVal less than 18724
	CMP R0, #28086        //Compare R0 with 28086
	BGT  Bproceed3        //Jump if potVal less than 28086
	MOVS R0, #3          //Assigning speed a value of 3
	RET                  //Returning the speed value
proceed3:
	MOVS R0, #25000
	CMP R0, #28087          //Compare potVal with 28087
	BLT  Bproceed4        //Jump if potVal less than 28087
	CMP R0, #37448        //Compare R0 with 37448
	BGT  Bproceed4        //Jump if potVal less than 37448
	MOVS R0, #4          //Assigning speed a value of 4
	RET                  //Returning the speed value
proceed4:
	MOVS R0, #36000
	CMP R0, #37449          //Compare potVal with 37449
	BLT  Bproceed5        //Jump if potVal less than 28087
	CMP R0, #48610        //Compare R0 with 48610
	BGT  Bproceed5       //Jump if potVal less than 48610
	MOVS R0, #5          //Assigning speed a value of 5
	RET                  //Returning the speed value
proceed5:
	MOVS R0, #50000
	CMP R0, #48611         //Compare potVal with 48611
	BLT  Bproceed6        //Jump if potVal less than 48611
	CMP R0, #56172        //Compare R0 with 56172
	BGT  Bproceed6       //Jump if potVal less than 48610
	MOVS R0, #6          //Assigning speed a value of 6
	RET                  //Returning the speed value
proceed6:
	MOVS R0, #58000
	CMP R0, #56173          //Compare potVal with 56173
	BLT  Bdone        //Jump if potVal less than 56173
	CMP R0, #65535        //Compare R0 with 65535
	BGT  Bdone       //Jump potVal if less than 65535
	MOVS R0, #7          //Assigning speed a value of 7
	RET                  //Returning the speed value
done:
	NOP
	BX LR
	.end