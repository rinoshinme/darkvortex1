#include "parser.h"
#include "utils.h"

Parser::Parser()
{
    net_param.net_props.clear();
    layer_params.clear();
}

bool Parser::parseModel(const std::string& model_file)
{
    std::vector<std::string> lines;
    bool ret = readLines(model_file, lines);
    if (!ret)
        return false;
    
    
    
    return true;
}
