
vector<string> NoProblem(int start, vector<int> created, vector<int> needed) {

    // your code 
    vector<string> output;
    int curr = start;
    for(size_t i = 0; i < created.size(); i ++){
    	if(curr >= needed[i]){
    		output.push_back("No problem! :D");
    		curr = curr - needed[i];
    	}else{
    		output.push_back("No problem. :(");
    	}
    	curr = curr + created[i];
    }
    return output;
}
