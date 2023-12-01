#include "controller.h"
#include "logger.h"
#include "model.h"
#include "view.h"

#include <iostream>
#include <tuple>
#include <memory>
#include <string>
#include <vector>

#include <stdlib.h>

static bool run = true;

void term()
{
    run = false;
}

/**
 * 05-homework
 **/
int main()
{ 
    auto db = std::make_shared<custom::IDatabase*>(new custom::Database());
    
    const auto info = custom::FileInfo(std::string("~/drawing.vec"));
    auto doc = std::shared_ptr<custom::Document>(new custom::Document(info, db));
    
    while(run)
    {
        // program loop
    }
    return 0;
}
