#include <iostream>

#include <soci/soci.h>
#include <soci/firebird/soci-firebird.h>
#include <filesystem>

using namespace soci;

int main() {
    /**
     * Read the README.md file and create a database db_cmake.fdb inside this folder,
     * where user=SYSDBA and password=masterkey.
     */

    std::string dbfile = (std::filesystem::current_path() / "db_cmake.fdb").string();
    session sql(firebird, "service=" + dbfile + " user=SYSDBA password=masterkey");

    try
    {
        sql << "drop table test1";
    }
    catch (soci_error const &)
    {} // ignore if error

    sql << "create table test1 (id integer)";

    // After DDL statement transaction must be commited or changes
    // won't be visible to active transaction.
    sql.commit();

    // After commit or rollback, transaction must be started manually.
    sql.begin();

    sql << "insert into test1(id) values(5)";

    int count;
    sql << "select count(*) from test1", into(count);

    std::cout << "count: " << count << std::endl;

    sql << "drop table test1";

    return 0;
}