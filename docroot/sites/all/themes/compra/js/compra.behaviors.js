(function ($) {
  var sameHeightProduct = function(selector){
    var maxHeight = 0;
    $(selector).css({height: "auto"});
    $(selector).each(function() {
      var currentHeight = $(this).outerHeight();
       if(currentHeight > maxHeight){
         maxHeight = currentHeight;
       }
     });
     
    $(selector).height(maxHeight);
  };

  Drupal.behaviors.compraBehavior = {
    attach: function (context, settings) {
      var selector = '.view-catalog-search-api .views-row h2.node__title';

      $(window).load(function(){
        sameHeightProduct(selector);
      });
      $(window).resize(function(){
        sameHeightProduct(selector);
      });
      
      $(window).scroll(function(){
        var headerOffset = $('.l-header').height();
        var windowScrollTop = $(window).scrollTop();
        var tolerance = headerOffset/2;
        
        if((headerOffset + tolerance) < windowScrollTop && !$('.l-header').hasClass('scrolled')){
          $('.l-header').hide();
          $('.l-header').addClass('scrolled');
          $('.l-header').fadeIn(150);
        }
        else if((headerOffset - tolerance) > windowScrollTop && $('.l-header').hasClass('scrolled')){
          $('.l-header').removeClass('scrolled');
        }
        
        
      });
    }
  };

})(jQuery);
