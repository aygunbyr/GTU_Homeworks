from django.urls import path, re_path
from .views import *

app_name = 'post'

urlpatterns = [
    path('index/', post_index, name='index'),
    path('create/', post_create, name='create'),
    path('categories/', category_view, name='categories'),
    re_path(r'^(?P<slug>[\w-]+)/$', post_detail, name='detail'),
    re_path(r'^(?P<slug>[\w-]+)/update/$', post_update, name='update'),
    re_path(r'^(?P<slug>[\w-]+)/delete/', post_delete, name='delete'),
]
