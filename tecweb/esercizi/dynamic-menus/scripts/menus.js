/**
 * Created by Giacomo on 12/11/2014.
 */

var menuHoriz = $('#menuOne li');
var menuVert = $('.menuVert');
for (var i=0; i<menuHoriz.length; ++i) {
    menuHoriz[i].addEventListener('mouseover', function() {
        var index1 = $(this).index();
        $(menuVert[index1]).css('margin-left', index1*74 + 'px');
        $(menuVert[index1]).css('display', 'inline-block');
    });
    menuHoriz[i].addEventListener('mouseout', function() {
        var index2 = $(this).index();
        $(menuVert[index2]).css('display', 'none');
    });
    menuVert[i].addEventListener('mouseover', function() {
        $(this).css('display', 'inline-block');
    });
    menuVert[i].addEventListener('mouseout', function() {
        $(this).css('display', 'none');
    });
}