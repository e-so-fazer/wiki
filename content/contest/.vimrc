set cin ai is ts=4 sw=4 nu rnu
" Select a region and then type :Hash
ca Hash w !cpp -dD -P -fpreprocessed \| tr -d '[:space:]' \
 \| md5sum \| cut -c-6
