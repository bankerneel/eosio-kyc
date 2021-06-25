void identity::add(const eosio::name status,
                   const string hashdata)
{
    // validation
    require_auth(get_self());
    //assigning auto increment number
    auto user_id = _identity.available_primary_key();
    // scoped identity table
    auto identity_itr = _identity.find(user_id);

    // modify existing identity
    if (identity_itr != _identity.end())
    {
        _identity.modify(identity_itr, get_self(), [&](auto &row) {
            row.user_id = user_id;
            row.status = status;
            row.hashdata = hashdata;
            row.trx_id = get_trx_id();
            row.timestamp = current_time_point();
        });
        // add identity
    }
    else
    {
        _identity.emplace(get_self(), [&](auto &row) {
            row.user_id = user_id;
            row.status = status;
            row.hashdata = hashdata;
            row.trx_id = get_trx_id();
            row.timestamp = current_time_point();
        });
    }
}
