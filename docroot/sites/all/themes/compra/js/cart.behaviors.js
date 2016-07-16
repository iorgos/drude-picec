(function ($) {

  Drupal.behaviors.cartBehavior = {
    attach: function (context, settings) {
      var button = '<a id="cart-more" href="#">' + Drupal.t("Show cart") + '</a>';
      $('#block-commerce-cart-cart .cart-contents').hide();
      $('#block-commerce-cart-cart .block__title').after(button);
      
      
      $('#cart-more').click(function(){
        var cartHidden, linkText;
        cartHidden = ($('#block-commerce-cart-cart .cart-contents:hidden').length === 0);
        $('#block-commerce-cart-cart .cart-contents').toggle('fast');
        linkText = cartHidden ? Drupal.t("Show cart") : Drupal.t("Hide cart");
        $(this).html(linkText);
        return false;
      });

    }
  };

})(jQuery);