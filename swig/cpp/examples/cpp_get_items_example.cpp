/**
 * @file cpp_get_items_example.cpp
 * @author Mislav Novakovic <mislav.novakovic@gmail.com>
 * @brief Example usage of get_items function
 *
 * @copyright
 * Copyright 2016 Deutsche Telekom AG.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <iostream>

#include "Session.h"

using namespace std;

int
main(int argc, char **argv)
{
    try {
        S_Connection conn(new Connection("app2"));

        S_Session sess(new Session(conn));

        const char *xpath = "/ietf-interfaces:interfaces/interface";

	auto values = sess->get_items(xpath);
        if (values == NULL)
            return 0;

	for(unsigned int i = 0; i < values->val_cnt(); i++)
            cout << values->val(i)->xpath() << endl;
    } catch( const std::exception& e ) {
        cout << e.what() << endl;
    }

    return 0;
}
