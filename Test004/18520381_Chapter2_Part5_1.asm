        ORG 0000H
        LJMP MAIN 
        ORG 000BH 
        CPL P2.1 
        RETI
        ORG 0030H    
    
MAIN:   MOV TMOD,#02H 
        MOV TH0,#-50 
        SETB TR0
		MOV IE, #82H
		SJMP $
        END 