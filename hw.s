.name "hay hay"
.comment "300 baks"

live:	live %0
		zjmp %:live
		live %0
		fork %-11
		live %0
		fork %-11

l2:		
		zjmp %:live
		and r1, %0, r1
		zjmp %:l2
