from django.urls import path, re_path
from payment import views

app_name = 'payment'

urlpatterns = [
    #re_path(r'^charge/$', views.charge, name="charge"), 
    path('charge/<int:trainer_id>', views.charge, name='charge'),
]