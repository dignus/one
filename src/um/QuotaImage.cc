/* -------------------------------------------------------------------------- */
/* Copyright 2002-2012, OpenNebula Project Leads (OpenNebula.org)             */
/*                                                                            */
/* Licensed under the Apache License, Version 2.0 (the "License"); you may    */
/* not use this file except in compliance with the License. You may obtain    */
/* a copy of the License at                                                   */
/*                                                                            */
/* http://www.apache.org/licenses/LICENSE-2.0                                 */
/*                                                                            */
/* Unless required by applicable law or agreed to in writing, software        */
/* distributed under the License is distributed on an "AS IS" BASIS,          */
/* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.   */
/* See the License for the specific language governing permissions and        */
/* limitations under the License.                                             */
/* -------------------------------------------------------------------------- */

#include "QuotaImage.h"

/* -------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */

const char * QuotaImage::IMAGE_METRICS[] = {"RVMS"};

const int QuotaImage::NUM_IMAGE_METRICS  = 1;

/* -------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */

bool QuotaImage::check(Template * tmpl,  string& error)
{
    vector<Attribute*> disks;
    VectorAttribute *  disk;

    string image_id;
    int num;

    map<string, int> image_request;

    image_request.insert(make_pair("RVMS",1));

    num = tmpl->get("DISK", disks);

    for (int i = 0 ; i < num ; i++)
    {
        disk = dynamic_cast<VectorAttribute *>(disks[i]);

        if ( disk == 0 )
        {
            continue;
        }

        image_id = disk->vector_value("IMAGE_ID");
        
        if ( !image_id.empty() )
        {
            return check_quota(image_id, image_request, error);
        }
    }

    return true;
}

/* -------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */

void QuotaImage::del(Template * tmpl)
{

    vector<Attribute*> disks;
    VectorAttribute *  disk;

    string image_id;
    int num;

    map<string, int> image_request;

    image_request.insert(make_pair("RVMS",1));

    num = tmpl->get("DISK", disks);

    for (int i = 0 ; i < num ; i++)
    {
        disk = dynamic_cast<VectorAttribute *>(disks[i]);

        if ( disk == 0 )
        {
            continue;
        }

        image_id = disk->vector_value("IMAGE_ID");
        
        del_quota(image_id, image_request);
    }
}

/* -------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */