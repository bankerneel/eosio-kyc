void identity::clean()
{
    require_auth(get_self());

    // identity
    auto identity_itr = _identity.begin();
    while (identity_itr != _identity.end())
    {
        identity_itr = _identity.erase(identity_itr);
    }
}