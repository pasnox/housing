/recherche/
<announcements summary="{resumeSansTri}" found="{nbTrouvees}" visible="{nbAffichables}" page="{pageCourante}" totalPage="{pageMax}" >
{
    //annonce/
    <announcement id="{idAnnonce}" url="{permaLien}" created="{dtCreation}" updated="{dtFraicheur}" >
        <informations thumbnail="{firstThumb}" title="{titre}" label="{libelle}" description="{descriptif}" />
        <pricing price="{prix}" currency="{prixUnite}" mention="{prixMention}" />
        <location id="{idPays}" country="{pays}" zip="{cp}" insee="{codeInsee}" city="{ville}" latitude="{latitude}" longitude="{longitude}" near="{proximite}" precision="{llPrecision}" dpe="{typeDPE}" />
        <contact id="{contact/idPublication}" audiotel="{contact/siAudiotel}" name="{contact/nom}" siren="{contact/rcsSiren}" nic="{contact/rcsNic}" />
        <details houseSurface="{surface}" surfaceUnite="{surfaceUnite}" loungeSurface="{surfsejour}" year="{anneeconstruct}" />
        <numbers rooms="{nbPiece}" bedrooms="{nbChambre}" bathrooms="{nbsallesdebain}" showerrooms="{nbsalleseau}" wc="{nbtoilettes}" parkings="{nbparkings}" boxes="{nbboxes}" terraces="{nbterrasses}" />
		<features unused="{siLotNeuf}" exclusive="{siMandatExclusif}" star="{siMandatStar}" terrace="{siterrasse}" pool="{sipiscine}" lounge="{sisejour}" />
        {
            photos//photo/
            <photo url="{bigUrl}" width="{bigwidth}" height="{bigheight}" />
        }
    </announcement>
}
</announcements>