l=($(ls -d */))
for file in "${l[@]}"; do 
    # echo "$i"; 
    if [[ -d $file ]]; then
        echo "$file proccesing"
        folder=($(ls ${file}))
        for im in "${folder[@]}"; do
            if [[ "$im" == *TIF ]]
            then
                echo "opening file ${file}/${im}"
                eog ${file}/${im}
            fi
        done
    fi

done