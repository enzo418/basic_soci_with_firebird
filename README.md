## 1. Download firebird
- Easy: sudo apt-get install firebird-dev firebird3.0-utils


- Hard: download from https://firebirdsql.org/en/firebird-4-0/

  - execute install as root

  - open the file "manifest.txt" and search for the library file
  
  - **IMPORTANT** add /opt/firebird/lib/ or wherever it installed the libs to the LD path, e.g. export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib/:/opt/firebird/lib/
  , modifying your .bash or .zshrc file.

## 2. Build soci with firebird:
   - Download soci https://sourceforge.net/projects/soci/


   - `cd soci && mkdir build && cd build`
   

   - `cmake .. -DSOCI_CXX11=ON -DSOCI_FIREBIRD_EMBEDDED=ON -DWITH_BOOST=OFF -DWITH_MYSQL=OFF -DWITH_ORACLE=OFF -DWITH_DB2=OFF -DWITH_SQLITE3=OFF -DSOCI_STATIC=OFF -DFIREBIRD_LIBRARIES="/opt/firebird/lib/libfbclient.so"DWITH_FIREBIRD=ON`
     
    FIREBIRD_LIBRARIES may not be needed if you used the package manager to install firebird.
   - `make -j4`


   - `sudo make install`


   - `sudo ldconfig`

## 3. Create the database
- run `sudo isql-fb` if installed using the package
- else run as `sudo isql` where it installed (/opt/firebird/bin/ in my case)


- execute the following line replacing the path to somewhere else and set some user and password to connect to that database


- `CREATE DATABASE '/home/user/database.fdb' USER 'SYSDBA' PASSWORD 'masterkey';`

## Alter the database
- with `sudo isql` run
- `CREATE TABLE PERSONS (NAME VARCHAR(30));`
- `SHOW TABLE PERSONS;`

## EXIT
- run `QUIT;`

## MORE:
[FIREBIRD DOCUMENTATION](https://www.firebirdsql.org/file/documentation/html/en/refdocs/fblangref40/firebird-40-language-reference.html)

## Can't open the file
### Operating system directive open failed
It's probably due to a permissions problem, since we are creating the file with sudo the owner is `root`

[detailed](http://www.firebirdfaq.org/faq102/)

1. Change the owner `sudo chown firebird database.fdb`
2. Change the group `sudo chgrp firebird database.fdb`
3. Add the user to the group `sudo usermod -a -G firebird username`
4. log out and log in again

### Unsupported on-disk structure for file {filename}; found 13.0, support 12.2
It's probably due to linking the wrong library, you can check the linked libraries with
`system("ldd ./soci_firebird_cmake");` inside the c++ code. In my case `libfbclient.so.2` was linking to
`/lib/x86_64-linux-gnu/libfbclient.so.2` but all my files of the firebird library are in /opt/ so I just
replaced it with the correct one, `sudo cp /opt/firebird/lib/libfbclient.so.2 /lib/x86_64-linux-gnu/libfbclient.so.2`.


This happens when the library was already installed, and then you created the database with isql that was linked to
`/foo/bar/libfbclient.so`, different from the `/moo/mar/libfbclient.so` used in your compiled program.

