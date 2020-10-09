 #!/usr/bin/env bash 
 folders=("include" "includes" "src" "source" "sources" "test" "tests")
 for folder in "${folders[0]}"
 do
  echo ${folder}
  if [[ -d ${folder} ]]; then
    command="cpplint --recursive ${folder}/*"
    echo ${command}
    if ${command} | grep "error"; then
      echo "::error :: Review your Code"
      exit 1
    fi
  fi
done
