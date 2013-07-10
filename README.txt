-- DEPENDENCIES --

You must install the 7.x-2.x-dev version of the jquery_update module. This gives
the possibility to use jquery 1.7 or greater.
http://drupal.org/project/jquery_update

Install the libraries module too: http://drupal.org/project/libraries

Then you need to download the SocialCount zip file and decompress it
in sites/all/libraries
https://raw.github.com/filamentgroup/SocialCount/master/dist/socialcount.zip
When the file is decompressed you should have this file for instance:
sites/all/libraries/socialcount/socialcount.js

In order to get the share counts PHP5 with curl are required.


-- INSTALLATION --

The SocialCount library require jQuery 1.6 so once the jquery_update module is
installed you need to configure it: admin/config/development/jquery_update
On the configuration page you must define a jquery version >= 1.7


-- CONFIGURATION --

To add the social count buttons to different you have to create new fields
in admin/structure/types/manage/NODE_TYPE/fields . You can then configure it
and place it like any other field.

For pages that are not nodes, there is also a block 'Social Count block'.
