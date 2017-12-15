# #!/bin/bash

echo INIT SEQUENTIAL EXPERIMENTS!!
for i in {1..30}                                                                                                                                                                                                                                                               
#for i in {1..3}
do                                                                                                                                                                                                                                                                             
	# for problem in problem1 problem2 problem3
	for problem in problem1 problem3
	do 
		for exec in sequential
		do
			for metric in runtime miss
			do
				for tec in DOD OOD
				do
					for circuit in superblue18 superblue4 superblue16 superblue5 superblue1 superblue3 superblue10 superblue7                                                                                                                                                                            
					# for circuit in superblue18 superblue4
					do
						# if [ $exec == "sequential" ]
						# then 
							echo command:
							echo ./hwloc-bind pu:0 ./ophidian_experiments [$problem][$tec][$exec][$metric] --ckt $circuit --oExp ./results/$problem/$metric\_$exec\_$problem\_$tec\_$circuit.txt
							./hwloc-bind pu:0 ./ophidian_experiments [$problem][$tec][$exec][$metric] --ckt $circuit --oExp ./results/$problem/$metric\_$exec\_$problem\_$tec\_$circuit.txt
							echo finish execution steep
						# else
						# 	echo command:
						# 	echo ./hwloc-bind pu:0-3 ./ophidian_experiments [$problem][$tec][$exec][$metric] --ckt $circuit --oExp ./results/$problem/$metric\_$exec\_$problem\_$tec\_$circuit.txt
						# 	./hwloc-bind pu:0-3 ./ophidian_experiments [$problem][$tec][$exec][$metric] --ckt $circuit --oExp ./results/$problem/$metric\_$exec\_$problem\_$tec\_$circuit.txt
						# 	echo finish execution steep
						# fi
					done
				done	
			done
		done
	done                                                                                                                                                                                                                                                           
 done

echo FINISH SEQUENTIAL EXPERIMENTS!!
echo INIT PARALLEL EXPERIMENTS!!

for i in {1..30}
do                                                                                                                                                                                                                                                                             
	# for problem in problem1 problem2 problem3
	for problem in problem1 problem3
	do 
		for exec in parallel
		do
			for metric in runtime miss
			do
				for tec in DOD OOD
				do
					for circuit in superblue18 superblue4 superblue16 superblue5 superblue1 superblue3 superblue10 superblue7                                                                                                                                                                            
					# for circuit in superblue18 superblue4
					do
						# if [ $exec == "sequential" ]
						# then 
						# 	echo command:
						# 	echo ./hwloc-bind pu:0 ./ophidian_experiments [$problem][$tec][$exec][$metric] --ckt $circuit --oExp ./results/$problem/$metric\_$exec\_$problem\_$tec\_$circuit.txt
						# 	./hwloc-bind pu:0 ./ophidian_experiments [$problem][$tec][$exec][$metric] --ckt $circuit --oExp ./results/$problem/$metric\_$exec\_$problem\_$tec\_$circuit.txt
						# 	echo finish execution steep
						# else
							echo command:
							echo ./hwloc-bind pu:0-3 ./ophidian_experiments [$problem][$tec][$exec][$metric] --ckt $circuit --oExp ./results/$problem/$metric\_$exec\_$problem\_$tec\_$circuit.txt
							./hwloc-bind pu:0-3 ./ophidian_experiments [$problem][$tec][$exec][$metric] --ckt $circuit --oExp ./results/$problem/$metric\_$exec\_$problem\_$tec\_$circuit.txt
							echo finish execution steep
						# fi
					done
				done	
			done
		done
	done                                                                                                                                                                                                                                                           
 done


echo FINISH EXPERIMENTS!!
