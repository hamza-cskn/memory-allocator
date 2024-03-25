echo "Fixing norm violations..."
sed -i'.bak' 's/FREE_MEMORY/free/g' aborter.c
sed -i'.bak' 's/FREE_MEMORY/free/g' allocator.c
sed -i'.bak' 's/ALLOCATE_MEMORY/malloc/g' allocator.c
sed -i'.bak' 's/ALLOCATE_MEMORY/malloc/g' allocator.c
sed -i'.bak' 's/#include "allocator-testable.h"/#include "allocator.h"/g' aborter.c
sed -i'.bak' 's/#include "allocator-testable.h"/#include "allocator.h"/g' allocator.c
read -p "Do you want to remove the backup files? (suggested) [y/n] " -n 1 -r
echo
if [[ $REPLY =~ ^[Yy]$ ]]
then
	rm *.bak
fi
echo "Done!"
norminette aborter.c allocator.c allocator.h
if [ $? -eq 0 ]
then
	echo "All norm violations fixed!"
else
	echo "There are still norm violations. Something gone wrong."
fi