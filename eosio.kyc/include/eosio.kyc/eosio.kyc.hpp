#include <eosio/eosio.hpp>
#include <eosio/system.hpp>
#include <eosio/crypto.hpp>

#include "get_trx_id.hpp"

#include <string>

using namespace eosio;
using namespace std;

class [[eosio::contract("eosio.kyc")]] identity : public contract
{
public:
   using contract::contract;

   /**
     * Construct a new contract given the contract name
     *
     * @param {name} receiver - The name of this contract
     * @param {name} code - The code name of the action this contract is processing.
     * @param {datastream} ds - The datastream used
     */
   identity(name receiver, name code, eosio::datastream<const char *> ds)
       : contract(receiver, code, ds),
         _identity(get_self(), get_self().value)
   {
   }

   /**
     * ACTION `add`
     *
     * Add identity report to the smart contract table
     *
     * - Authority: `get_self()`
     *
     * @param {string} status - KYC status for particular email pending/approved
     * @param {string} hashdata - additional hashdata about user
     *
     * @example
     *
     * cleos push action kycaccount add '["pending", "randomhash"]' -p kycaccount
     */
   [[eosio::action]] void add(const eosio::name status,
                              const string hashdata);

   /**
     * ACTION `clean`
     *
     * removes all rows from existing tables
     *
     * - Authority: `get_self()`
     */
   [[eosio::action]] void clean();

   using add_action = eosio::action_wrapper<"add"_n, &identity::add>;

private:
   /**
     * TABLE `identity`
     *
     * @param {string} status - KYC status either pending or approved
     * @param {string} hashdata - additional hashdata about user information
     * @param {checksum256} trx_id - identity creation transaction id
     * @param {time_point_sec} timestamp - identity creation timestamp
     *
     * @example
     *
     * {
     *   "status": "pending",
     *   "hashdata": "randomhash",
     *   "trx_id": "f0889d11501fc83ff52d8af62e2d1552193c728e874d9bb559f30a0012deee3e",
     *   "timestamp": "2019-09-09T00:00:00"
     * }
     */
   struct [[eosio::table("identity")]] identity_row
   {
      uint64_t user_id;
      eosio::name status;
      string hashdata;
      checksum256 trx_id;
      time_point_sec timestamp;

      uint64_t primary_key() const { return user_id; }
   };

   // Table
   typedef multi_index<"identity"_n, identity_row> identity_table;

   // local instances of the multi indexes
   identity_table _identity;

   // private helpers
   // ===============
};