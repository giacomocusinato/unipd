/**
 * Created by Giacomo on 12/11/2014.
 */
var menuHoriz = $('#menuOne li');
var menuVert = $('.menuVert');
var subMenus = $('#subMenus');
for (var i=0; i<menuHoriz.length; ++i) {
    menuHoriz[i].addEventListener('mouseover', function() {
        var index1 = $(this).index();
        $(menuVert[index1]).css('display', 'inline-block');
        for (var j=0; j<menuVert.length; j++) {
            if (j!=index1) {
                $(menuVert[j]).css('display', 'none');
            }
        }
        $(subMenus).css('display', "inline-block");
    });
}
$('header, #container').on('mouseover', function() {
   $(subMenus).css('display', 'none');
    console.log('mouseout');
});