sdir=./src/
odir=./obj/
idir=./include/

srcd=$(wildcard $(sdir)*.cpp) 			#从当前目录查找所有.cpp文件
src=$(notdir $(srcd))    				#只保留文件名去除路径
obj=$(patsubst %.cpp,$(odir)%.o,$(src))	#将.cpp文件名替换为.o
target=myproject

$(target):$(obj)
	g++ -g $^ -o $@  -I`mysql_config --cflags --libs`
$(odir)%.o:$(sdir)%.cpp  #%类似于通配符
#g++ -g -c $< -o $@ -I$(idir)
	g++ -g -c $^ -o $@ -I$(idir) -I`mysql_config --cflags --libs`

.PHONY:clean #声明clean为伪目标（并不是要生成一个名为clean的目标只是执行其命令），不进行更新比对
clean:
	rm $(obj) $(target) -f    
#-f表示强制执行不管文件是否存在

#makefile中的自动变量，只能在命令中使用
# $@表示目标
# $<表示依赖项中第一项
# $^表示所有依赖项
