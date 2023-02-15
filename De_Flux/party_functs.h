


///erases parties sent to it.
void party_erase(struct party *datparty){
	int i;
	
	datparty->partyType = pt_friendly;
	datparty->playerDeployed = false;
	
	for(i=0; i<MAX_PARTY_MEMBERS; i++){
		being_erase(&datparty->beings[i]);
	}
	for(i=0; i<MAX_PARTY_MEMBERS_DEPLOYED; i++){
		datparty->deployed[i] = 0;
	}
}


///initializes the parties
void party_init(){
	party_erase(&playerParty);
	
}
