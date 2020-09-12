.name "zorg u dead"
.comment "Born to zorg kill"

debut:	lfork	%2048
		sti r1, %:hello, %1
		live %1
		fork	%:hello
		and r3, %0, r3
		zjmp %:body


body:	live 	%1
		and r3, %0, r3
		zjmp	%:body

hello:	live %1
		and r3, %0, r3